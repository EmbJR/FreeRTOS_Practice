/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * This is the MPLAB/PIC18F port for the xc8 v3 compiler.
 *
 * Original C18 / xc8 v1/v2 port written by various FreeRTOS contributors.
 * Rewritten for xc8 v3 by replacing the legacy #asm/#endasm blocks with
 * the xc8 v3 asm("...") inline assembly form. C symbols are referenced
 * by their assembler name (prefixed with an underscore).
 */

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the PIC port.
 *----------------------------------------------------------*/

/* Hardware setup for tick. */
#define portTIMER_FOSC_SCALE            ( ( uint32_t ) 4 )

/* Initial interrupt enable state for newly created tasks.  This value is
copied into INTCON when a task switches in for the first time. */
#define portINITAL_INTERRUPT_STATE          0xc0

/* Just the bit within INTCON for the global interrupt flag. */
#define portGLOBAL_INTERRUPT_FLAG           0x80

/* Constant used for context switch macro when we require the interrupt
enable state to be unchanged when the interrupted task is switched back in. */
#define portINTERRUPTS_UNCHANGED            0x00

/* Some memory areas get saved as part of the task context.  These memory
area's get used by the compiler for temporary storage, especially when
performing mathematical operations, or when using 32bit data types.  This
constant defines the size of memory area which must be saved. */
#define portCOMPILER_MANAGED_MEMORY_SIZE    ( ( uint8_t ) 0x13 )

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
typedef void TCB_t;
extern volatile TCB_t * volatile pxCurrentTCB;

/* IO port constants. */
#define portBIT_SET     ( ( uint8_t ) 1 )
#define portBIT_CLEAR   ( ( uint8_t ) 0 )

/*
 * The serial port ISR's are defined in serial.c, but are called from portable
 * as they use the same vector as the tick ISR.
 */
extern void vSerialTxISR( void );
extern void vSerialRxISR( void );

/*
 * Perform hardware setup to enable ticks.
 */
static void prvSetupTimerInterrupt( void );

/*
 * ISR to maintain the tick, and perform tick context switches if the
 * preemptive scheduler is being used.
 */
static void prvTickISR( void );

/*
 * ISR placed on the low priority vector.  This calls the appropriate ISR for
 * the actual interrupt.
 */
static void prvLowInterrupt( void );

/*
 * Macro that pushes all the registers that make up the context of a task onto
 * the stack, then saves the new top of stack into the TCB.
 *
 * If this is called from an ISR then the interrupt enable bits must have been
 * set for the ISR to ever get called.  Therefore we want to save the INTCON
 * register with the enable bits forced to be set - and ucForcedInterruptFlags
 * must contain these bit settings.  This means the interrupts will again be
 * enabled when the interrupted task is switched back in.
 *
 * If this is called from a manual context switch (i.e. from a call to yield),
 * then we want to save the INTCON so it is restored with its current state,
 * and ucForcedInterruptFlags must be 0.  This allows a yield from within
 * a critical section.
 *
 * The compiler uses some locations at the bottom of the memory for temporary
 * storage during math and other computations.  This is especially true if
 * 32bit data types are utilized (as they are by the scheduler).  The .tmpdata
 * and MATH_DATA sections have to be stored in there entirety as part of a task
 * context.  This macro stores from data address 0x00 to
 * portCOMPILER_MANAGED_MEMORY_SIZE.  This is sufficient for the demo
 * applications but you should check the map file for your project to ensure
 * this is sufficient for your needs.  It is not clear whether this size is
 * fixed for all compilations or has the potential to be program specific.
 */
#define portSAVE_CONTEXT( ucForcedInterruptFlags )                              \
{                                                                               \
    /* Save WREG, STATUS, INTCON (with forced flags). */                        \
    asm( "movff WREG, PREINC1" );                                               \
    asm( "movff STATUS, PREINC1" );                                             \
    asm( "movff INTCON, WREG" );                                                \
    asm( "iorlw %0" :: "i" ( ucForcedInterruptFlags ) );                        \
    asm( "movff WREG, PREINC1" );                                               \
                                                                                \
    portDISABLE_INTERRUPTS();                                                   \
                                                                                \
    /* Store the necessary registers to the stack. */                           \
    asm( "movff BSR, PREINC1" );                                                \
    asm( "movff FSR2L, PREINC1" );                                              \
    asm( "movff FSR2H, PREINC1" );                                              \
    asm( "movff FSR0L, PREINC1" );                                              \
    asm( "movff FSR0H, PREINC1" );                                              \
    asm( "movff TABLAT, PREINC1" );                                             \
    asm( "movff TBLPTRU, PREINC1" );                                            \
    asm( "movff TBLPTRH, PREINC1" );                                            \
    asm( "movff TBLPTRL, PREINC1" );                                            \
    asm( "movff PRODH, PREINC1" );                                              \
    asm( "movff PRODL, PREINC1" );                                              \
    asm( "movff PCLATU, PREINC1" );                                             \
    asm( "movff PCLATH, PREINC1" );                                             \
    /* Store the .tempdata and MATH_DATA areas. */                              \
    asm( "clrf FSR0L, c" );                                                     \
    asm( "clrf FSR0H, c" );                                                     \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff POSTINC0, PREINC1" );                                           \
    asm( "movff INDF0, PREINC1" );                                              \
    asm( "movff FSR0L, PREINC1" );                                              \
    asm( "movff FSR0H, PREINC1" );                                              \
    /* Store the hardware stack pointer in a temp register before we modify it.*/\
    asm( "movff STKPTR, FSR0L" );                                               \
                                                                                \
    /* Store each address from the hardware stack. */                           \
    while( STKPTR > ( uint8_t ) 0 )                                             \
    {                                                                           \
        asm( "movff TOSL, PREINC1" );                                           \
        asm( "movff TOSH, PREINC1" );                                           \
        asm( "movff TOSU, PREINC1" );                                           \
        asm( "pop" );                                                           \
    }                                                                           \
                                                                                \
    /* Store the number of addresses on the hardware stack. */                  \
    asm( "movff FSR0L, PREINC1" );                                              \
    asm( "movf PREINC1, 1, 0" );                                                \
                                                                                \
    /* Save the new top of the software stack in the TCB. */                    \
    asm( "movff _pxCurrentTCB, FSR0L" );                                        \
    asm( "movff _pxCurrentTCB + 1, FSR0H" );                                    \
    asm( "movff FSR1L, POSTINC0" );                                             \
    asm( "movff FSR1H, POSTINC0" );                                             \
}
/*-----------------------------------------------------------*/

/*
 * This is the reverse of portSAVE_CONTEXT.  See portSAVE_CONTEXT for more
 * details.
 */
#define portRESTORE_CONTEXT()                                                   \
{                                                                               \
    /* Set FSR0 to point to pxCurrentTCB->pxTopOfStack. */                      \
    asm( "movff _pxCurrentTCB, FSR0L" );                                        \
    asm( "movff _pxCurrentTCB + 1, FSR0H" );                                    \
                                                                                \
    /* De-reference FSR0 to set the address it holds into FSR1. */              \
    asm( "movff POSTINC0, FSR1L" );                                             \
    asm( "movff POSTINC0, FSR1H" );                                             \
                                                                                \
    /* How many return addresses are there on the hardware stack?  Discard     \
    the first byte as we are pointing to the next free space. */                \
    asm( "movff POSTDEC1, FSR0L" );                                             \
    asm( "movff POSTDEC1, FSR0L" );                                             \
                                                                                \
    /* Fill the hardware stack from our software stack. */                      \
    STKPTR = 0;                                                                 \
                                                                                \
    while( STKPTR < FSR0L )                                                     \
    {                                                                           \
        asm( "push" );                                                          \
        asm( "movf POSTDEC1, 0, 0" );                                           \
        asm( "movwf TOSU, 0" );                                                 \
        asm( "movf POSTDEC1, 0, 0" );                                           \
        asm( "movwf TOSH, 0" );                                                 \
        asm( "movf POSTDEC1, 0, 0" );                                           \
        asm( "movwf TOSL, 0" );                                                 \
    }                                                                           \
                                                                                \
    /* Restore the .tmpdata and MATH_DATA memory. */                             \
    asm( "movff POSTDEC1, FSR0H" );                                             \
    asm( "movff POSTDEC1, FSR0L" );                                             \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, POSTDEC0" );                                          \
    asm( "movff POSTDEC1, INDF0" );                                             \
    /* Restore the other registers forming the tasks context. */                \
    asm( "movff POSTDEC1, PCLATH" );                                            \
    asm( "movff POSTDEC1, PCLATU" );                                            \
    asm( "movff POSTDEC1, PRODL" );                                             \
    asm( "movff POSTDEC1, PRODH" );                                             \
    asm( "movff POSTDEC1, TBLPTRL" );                                           \
    asm( "movff POSTDEC1, TBLPTRH" );                                           \
    asm( "movff POSTDEC1, TBLPTRU" );                                           \
    asm( "movff POSTDEC1, TABLAT" );                                            \
    asm( "movff POSTDEC1, FSR0H" );                                             \
    asm( "movff POSTDEC1, FSR0L" );                                             \
    asm( "movff POSTDEC1, FSR2H" );                                             \
    asm( "movff POSTDEC1, FSR2L" );                                             \
    asm( "movff POSTDEC1, BSR" );                                               \
    /* The next byte is the INTCON register.  Read this into WREG as some       \
    manipulation is required. */                                                \
    asm( "movff POSTDEC1, WREG" );                                              \
                                                                                \
    /* From the INTCON register, only the interrupt enable bits form part       \
    of the tasks context.  It is perfectly legitimate for another task to       \
    have modified any other bits.  We therefore only restore the top two bits.  \
    */                                                                          \
    if( WREG & portGLOBAL_INTERRUPT_FLAG )                                      \
    {                                                                           \
        asm( "movff POSTDEC1, STATUS" );                                        \
        asm( "movff POSTDEC1, WREG" );                                          \
        /* Return enabling interrupts. */                                       \
        asm( "retfie 0" );                                                      \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        asm( "movff POSTDEC1, STATUS" );                                        \
        asm( "movff POSTDEC1, WREG" );                                          \
        /* Return without effecting interrupts.  The context may have           \
        been saved from a critical region. */                                   \
        asm( "return 0" );                                                      \
    }                                                                           \
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
uint32_t ulAddress;
uint8_t ucBlock;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *pxTopOfStack = 0x11;
    pxTopOfStack++;
    *pxTopOfStack = 0x22;
    pxTopOfStack++;
    *pxTopOfStack = 0x33;
    pxTopOfStack++;


    /* Simulate how the stack would look after a call to vPortYield() generated
    by the compiler.

    First store the function parameters.  This is where the task will expect to
    find them when it starts running. */
    ulAddress = ( uint32_t ) pvParameters;
    *pxTopOfStack = ( StackType_t ) ( ulAddress & ( uint32_t ) 0x00ff );
    pxTopOfStack++;

    ulAddress >>= 8;
    *pxTopOfStack = ( StackType_t ) ( ulAddress & ( uint32_t ) 0x00ff );
    pxTopOfStack++;

    /* Next we just leave a space.  When a context is saved the stack pointer
    is incremented before it is used so as not to corrupt whatever the stack
    pointer is actually pointing to.  This is especially necessary during
    function epilogue code generated by the compiler. */
    *pxTopOfStack = 0x44;
    pxTopOfStack++;

    /* Next are all the registers that form part of the task context. */

    *pxTopOfStack = ( StackType_t ) 0x66; /* WREG. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0xcc; /* Status. */
    pxTopOfStack++;

    /* INTCON is saved with interrupts enabled. */
    *pxTopOfStack = ( StackType_t ) portINITAL_INTERRUPT_STATE; /* INTCON */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x11; /* BSR. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x22; /* FSR2L. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x33; /* FSR2H. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x44; /* FSR0L. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x55; /* FSR0H. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x66; /* TABLAT. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x00; /* TBLPTRU. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x88; /* TBLPTRUH. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x99; /* TBLPTRUL. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0xaa; /* PRODH. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0xbb; /* PRODL. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x00; /* PCLATU. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x00; /* PCLATH. */
    pxTopOfStack++;

    /* Next the .tmpdata and MATH_DATA sections. */
    for( ucBlock = 0; ucBlock <= portCOMPILER_MANAGED_MEMORY_SIZE; ucBlock++ )
    {
        *pxTopOfStack = ( StackType_t ) ucBlock;
        *pxTopOfStack++;
    }

    /* Store the top of the global data section. */
    *pxTopOfStack = ( StackType_t ) portCOMPILER_MANAGED_MEMORY_SIZE; /* Low. */
    pxTopOfStack++;

    *pxTopOfStack = ( StackType_t ) 0x00; /* High. */
    pxTopOfStack++;

    /* The only function return address so far is the address of the
    task. */
    ulAddress = ( uint32_t ) pxCode;

    /* TOS low. */
    *pxTopOfStack = ( StackType_t ) ( ulAddress & ( uint32_t ) 0x00ff );
    pxTopOfStack++;
    ulAddress >>= 8;

    /* TOS high. */
    *pxTopOfStack = ( StackType_t ) ( ulAddress & ( uint32_t ) 0x00ff );
    pxTopOfStack++;
    ulAddress >>= 8;

    /* TOS even higher. */
    *pxTopOfStack = ( StackType_t ) ( ulAddress & ( uint32_t ) 0x00ff );
    pxTopOfStack++;

    /* Store the number of return addresses on the hardware stack - so far only
    the address of the task entry point. */
    *pxTopOfStack = ( StackType_t ) 1;
    pxTopOfStack++;

    return pxTopOfStack;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
    /* Setup a timer for the tick ISR is using the preemptive scheduler. */
    prvSetupTimerInterrupt();

    /* Restore the context of the first task to run. */
    portRESTORE_CONTEXT();

    /* Should not get here.  Use the function name to stop compiler warnings. */
    ( void ) prvLowInterrupt;
    ( void ) prvTickISR;

    return pdTRUE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* It is unlikely that the scheduler for the PIC port will get stopped
    once running.  If required disable the tick interrupt here, then return
    to xPortStartScheduler(). */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  This is similar to the tick context switch,
 * but does not increment the tick count.  It must be identical to the
 * tick context switch in how it stores the stack of a task.
 */
void vPortYield( void )
{
    /* This can get called with interrupts either enabled or disabled.  We
    will save the INTCON register with the interrupt enable bits unmodified. */
    portSAVE_CONTEXT( portINTERRUPTS_UNCHANGED );

    /* Switch to the highest priority task that is ready to run. */
    vTaskSwitchContext();

    /* Start executing the task we have just switched to. */
    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Low-priority interrupt vector.  In xc8 v3, the low-priority interrupt
 * vector is a function with the __interrupt(low_priority) and
 * __interrupt_low_priority attributes, and the high-priority vector is
 * supplied via the interrupt_low() function pointer or by naming a
 * function with the appropriate attribute.
 */
void __interrupt( low_priority ) prvLowInterrupt( void )
{
    /* Was the interrupt the tick? */
    if( PIR1bits.CCP1IF )
    {
        asm( "goto _prvTickISR" );
    }

    /* Was the interrupt a byte being received? */
    if( PIR1bits.RCIF )
    {
        asm( "goto _vSerialRxISR" );
    }

    /* Was the interrupt the Tx register becoming empty? */
    if( PIR1bits.TXIF )
    {
        if( PIE1bits.TXIE )
        {
            asm( "goto _vSerialTxISR" );
        }
    }
}
/*-----------------------------------------------------------*/

/*
 * ISR for the tick.
 * This increments the tick count and, if using the preemptive scheduler,
 * performs a context switch.  This must be identical to the manual
 * context switch in how it stores the context of a task.
 */
static void prvTickISR( void )
{
    /* Interrupts must have been enabled for the ISR to fire, so we have to
    save the context with interrupts enabled. */
    portSAVE_CONTEXT( portGLOBAL_INTERRUPT_FLAG );
    PIR1bits.CCP1IF = 0;

    /* Maintain the tick count. */
    if( xTaskIncrementTick() != pdFALSE )
    {
        /* Switch to the highest priority task that is ready to run. */
        vTaskSwitchContext();
    }

    portRESTORE_CONTEXT();
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.
 */
static void prvSetupTimerInterrupt( void )
{
const uint32_t ulConstCompareValue = ( ( configCPU_CLOCK_HZ / portTIMER_FOSC_SCALE ) / configTICK_RATE_HZ );
uint32_t ulCompareValue;
uint8_t ucByte;

    /* Interrupts are disabled when this function is called.

    Setup CCP1 to provide the tick interrupt using a compare match on timer
    1.

    Clear the time count then setup timer. */
    TMR1H = ( uint8_t ) 0x00;
    TMR1L = ( uint8_t ) 0x00;

    /* Set the compare match value. */
    ulCompareValue = ulConstCompareValue;
    CCPR1L = ( uint8_t ) ( ulCompareValue & ( uint32_t ) 0xff );
    ulCompareValue >>= ( uint32_t ) 8;
    CCPR1H = ( uint8_t ) ( ulCompareValue & ( uint32_t ) 0xff );

    CCP1CONbits.CCP1M0 = portBIT_SET;   /*< Compare match mode. */
    CCP1CONbits.CCP1M1 = portBIT_SET;   /*< Compare match mode. */
    CCP1CONbits.CCP1M2 = portBIT_CLEAR; /*< Compare match mode. */
    CCP1CONbits.CCP1M3 = portBIT_SET;   /*< Compare match mode. */
    PIE1bits.CCP1IE = portBIT_SET;      /*< Interrupt enable. */

    /* Configure Timer1: 16-bit read/write, internal instruction cycle
    clock, 1:1 prescaler, CCP1 uses Timer1. */
    T1CON = ( uint8_t ) 0x00;
    T1CONbits.TMR1CS = 0;               /*< Internal clock (Fosc/4). */
    T1CONbits.T1CKPS0 = 0;              /*< 1:1 prescale. */
    T1CONbits.T1CKPS1 = 0;              /*< 1:1 prescale. */
    T1CONbits.T1OSCEN = 0;              /*< Oscillator off. */
    T1CONbits.T1SYNC = 1;               /*< Not used. */
    T1CONbits.RD16 = 1;                 /*< 16-bit read/write. */
    T1CONbits.TMR1ON = 1;               /*< Timer1 on. */

    /* We are only going to use the global interrupt bit, so set the peripheral
    bit to true. */
    INTCONbits.GIEL = portBIT_SET;
}
