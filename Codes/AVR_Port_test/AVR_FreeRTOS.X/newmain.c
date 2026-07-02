/*
 * File:   newmain.c
 * Author: Jaydeep
 *
 * Created on 28 June, 2026, 5:54 PM
 */

/*
 * Example 2: Timer usage WITH interrupts
 *
 * Demonstrates:
 *  - Timer0 COMPA ISR: 1 ms tick (used as a software timebase)
 *  - Timer1 OVF  ISR:  ~ 1 second tick (used to toggle an LED)
 *  - Timer3 COMPB ISR: button debounce / event handler
 *
 * Target: ATmega2560, F_CPU = 16 MHz
 * IDE:    Microchip MPLAB X with AVR-GCC toolchain
 *
 * Wiring (optional, for the LED portion):
 *   - LED on PB7 (Arduino Mega pin 13) - via the on-board LED
 *   - Push-button on PE4 (active low, internal pull-up enabled)
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "gpiom2560.h"
#include "Timerm2560.h"
#include "FreeRTOS.h"
#include "task.h"


#define LED1_PORT      GPIO_PORT_B
#define LED1_MASK      (1u << 7)              /* PH5 */
#define LED2_PORT      GPIO_PORT_B
#define LED2_MASK      (1u << 5)              /* PH5 */

#define BUTTON_PORT   GPIO_PORT_D
#define BUTTON_MASK   (1u << 2)              /* PD2 */


TaskHandle_t ledTask1Handle;
TaskHandle_t ledTask2Handle;

/* Flag toggled from Timer1 OVF ISR */
static volatile bool     schedInitdone = false;

volatile uint32_t g_millis = 0;

static void led_setup(void)
{
    GPIO_PinConfig_t led = {
        .port          = LED1_PORT,
        .pinMask       = LED1_MASK,
        .direction     = GPIO_DIR_OUTPUT,
        .initialLevel  = GPIO_LEVEL_LOW,
        .pullup        = GPIO_PULLUP_DISABLE
    };
    GPIO_Init(&led);
    led.port = LED2_PORT;
    led.pinMask = LED2_MASK;
    GPIO_Init(&led);
}

/* ---- ISRs (user code) ---- */

/* Timer0 COMPA - 1 ms tick */
static void on_t0_compa(void)
{
    //g_millis++;
    //if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) 
    {
  /* Call tick handler */
        //xTaskIncrementTick();
    }
}

void LedTask(void *pvParameters)
{

    /* Initialize xLastWakeTime with the current tick count */
    //xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        /* Toggle PA5 */
    	GPIO_TogglePins(LED1_PORT, LED1_MASK);  

        /* Wait until 100 ms from the previous wake time */
//        vTaskDelayUntil(
//            &xLastWakeTime,
//            pdMS_TO_TICKS(pdMS_TO_TICKS(500))
//        );
//		for(int i = 0; i<5000; i++)
//			for(int j = 0; j<50; j++);
    	vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Led2Task(void *pvParameters)
{

    /* Initialize xLastWakeTime with the current tick count */
    //xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        /* Toggle PA5 */
    	GPIO_TogglePins(LED2_PORT, LED2_MASK);  

        /* Wait until 100 ms from the previous wake time */
//        vTaskDelayUntil(
//            &xLastWakeTime,
//            pdMS_TO_TICKS(pdMS_TO_TICKS(500))
//        );
//		for(int i = 0; i<5000; i++)
//			for(int j = 0; j<50; j++);
    	vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    /* LED pin PB7 (Arduino D13) */
    led_setup();

    /* ---- Timer1 : Normal mode, overflow ~ 1 s ----
     * F_CPU = 16 MHz, prescaler = 256 -> 62.5 kHz
     * 16-bit overflow at 65536 -> 65536 / 62500 = 1.048576 s
     * Reload with 65536 - 62500 = 3036 each overflow for an exact 1 s.
     */
#if 0
    TimerConfig_t t0_cfg = {
        .timer     = TIMER1,
        .mode      = TIMER_MODE_CTC,
        .prescaler = TIMER_PRESCALER_32,
    };
    Timer_Init(&t0_cfg);
    Timer_SetCompareA(TIMER1, 125);
    Timer_RegisterCallback(TIMER1, TIMER_INT_COMPA, on_t0_compa);
    Timer_DisableInterrupt(TIMER1, TIMER_INT_COMPA);
        /* Globally enable interrupts */
    Timer_GlobalIrqEnable();
#endif
    
    xTaskCreate( LedTask, "LED1", 128, NULL, tskIDLE_PRIORITY + 2, &ledTask1Handle);
    
    xTaskCreate(Led2Task, "LED2", 128, NULL, tskIDLE_PRIORITY + 2, &ledTask2Handle);
    
    vTaskStartScheduler();
    //Timer_EnableInterrupt(TIMER1, TIMER_INT_COMPA);

    for (;;) {

    }

    return 0;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // Trigger a breakpoint or reset the system here
    while (1) {
        //GPIO_TogglePins(LED2_PORT, LED2_MASK);  
		//GPIO_TogglePin(GPIOC, GPIO_PIN_9);
        for(int i = 0; i<800; i++)
			for(int j = 0; j<50; j++);
	}
}

void vApplicationMallocFailedHook(void)
{
    while(1)
    {
        //GPIO_TogglePins(LED2_PORT, LED2_MASK);
        for(int i = 0; i<8000; i++)
			for(int j = 0; j<50; j++);
        /* Memory exhausted */
    }
}

void vApplicationIdleHook(void) {
    // This runs whenever no other task is ready to run
    // Enter Sleep Mode
    //__WFI(); 
    		//GPIO_TogglePin(GPIOC, GPIO_PIN_8);
            //Delay_ms(10);
    //GPIO_SetPins(LED2_PORT, LED2_MASK);
}