/*
 * gpiom2560.h
 *
 * Bare-metal GPIO driver for the ATmega2560 (also covers ATmega640/1280/2561).
 * Targets AVR-GCC (Microchip MPLAB X IDE / avr-gcc toolchain).
 *
 * Supports:
 *  - Digital input / output on all ports (PORTA..PORTL)
 *  - Internal pull-up enable on inputs
 *  - Direction, set, clear, toggle, read operations
 *  - Pin configuration struct (direction, initial level, pull-up)
 *  - Pin-change interrupts (PCINT0..PCINT3) on any GPIO pin
 *  - External interrupts (INT0..INT7) on dedicated pins with edge selection
 *  - Optional ISR callbacks registered by the user
 *
 * Register-level details are taken from the ATmega2560 datasheet
 * (Document 2549Q).
 */

#ifndef GPIOM2560_H_
#define GPIOM2560_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * I/O Register Definitions (memory-mapped I/O)
 * ============================================================ */

/* Port registers - using the standard AVR SFR names from <avr/io.h>.
 * We do not include <avr/io.h> here so this header can be parsed by
 * tools that do not know the part header, but every symbol is the
 * one defined by <avr/io.h> for ATmega2560. */
#define GPIO_PORTA   ((volatile uint8_t *)0x22)   /* PORTA */
#define GPIO_DDRA    ((volatile uint8_t *)0x21)   /* DDRA  */
#define GPIO_PINA    ((volatile uint8_t *)0x20)   /* PINA  */

#define GPIO_PORTB   ((volatile uint8_t *)0x25)   /* PORTB */
#define GPIO_DDRB    ((volatile uint8_t *)0x24)
#define GPIO_PINB    ((volatile uint8_t *)0x23)

#define GPIO_PORTC   ((volatile uint8_t *)0x28)
#define GPIO_DDRC    ((volatile uint8_t *)0x27)
#define GPIO_PINC    ((volatile uint8_t *)0x26)

#define GPIO_PORTD   ((volatile uint8_t *)0x2B)
#define GPIO_DDRD    ((volatile uint8_t *)0x2A)
#define GPIO_PIND    ((volatile uint8_t *)0x29)

#define GPIO_PORTE   ((volatile uint8_t *)0x2E)
#define GPIO_DDRE    ((volatile uint8_t *)0x2D)
#define GPIO_PINE    ((volatile uint8_t *)0x2C)

#define GPIO_PORTF   ((volatile uint8_t *)0x31)
#define GPIO_DDRF    ((volatile uint8_t *)0x30)
#define GPIO_PINF    ((volatile uint8_t *)0x2F)

#define GPIO_PORTG   ((volatile uint8_t *)0x34)
#define GPIO_DDRG    ((volatile uint8_t *)0x33)
#define GPIO_PING    ((volatile uint8_t *)0x32)

#define GPIO_PORTH   ((volatile uint8_t *)0x09C)
#define GPIO_DDRH    ((volatile uint8_t *)0x09B)
#define GPIO_PINH    ((volatile uint8_t *)0x09A)

#define GPIO_PORTJ   ((volatile uint8_t *)0x09F)
#define GPIO_DDRJ    ((volatile uint8_t *)0x09E)
#define GPIO_PINJ    ((volatile uint8_t *)0x09D)

#define GPIO_PORTK   ((volatile uint8_t *)0x0A2)
#define GPIO_DDRK    ((volatile uint8_t *)0x0A1)
#define GPIO_PINK    ((volatile uint8_t *)0x0A0)

#define GPIO_PORTL   ((volatile uint8_t *)0x0A5)
#define GPIO_DDRL    ((volatile uint8_t *)0x0A4)
#define GPIO_PINL    ((volatile uint8_t *)0x0A3)

/* External interrupt control */
#define EXTINT_EICRA    (*(volatile uint8_t *)0x069)  /* INT0..INT3 mode */
#define EXTINT_EICRB    (*(volatile uint8_t *)0x06A)  /* INT4..INT7 mode */
#define EXTINT_EIMSK    (*(volatile uint8_t *)0x03D)  /* INT enable mask  */
#define EXTINT_EIFR     (*(volatile uint8_t *)0x03C)  /* INT flag register */
#define EXTINT_PCICR    (*(volatile uint8_t *)0x068)  /* PCINT enable bank */
#define EXTINT_PCIFR    (*(volatile uint8_t *)0x03B)  /* PCINT flag bank   */
#define EXTINT_PCMSK0   (*(volatile uint8_t *)0x06B)  /* PCINT0..7  enable */
#define EXTINT_PCMSK1   (*(volatile uint8_t *)0x06C)  /* PCINT8..15 enable */
#define EXTINT_PCMSK2   (*(volatile uint8_t *)0x06D)  /* PCINT16 enable    */
#define EXTINT_PCMSK3   (*(volatile uint8_t *)0x073)  /* PCINT24 enable    */

/* SREG bit for global interrupt enable */
#define SREG_I_BIT      (7)

/* ============================================================
 * Public Types
 * ============================================================ */

typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
    GPIO_PORT_J,
    GPIO_PORT_K,
    GPIO_PORT_L,
} GPIO_Port_t;

typedef enum {
    GPIO_DIR_INPUT = 0,
    GPIO_DIR_OUTPUT
} GPIO_Direction_t;

typedef enum {
    GPIO_LEVEL_LOW  = 0,
    GPIO_LEVEL_HIGH = 1
} GPIO_Level_t;

typedef enum {
    GPIO_PULLUP_DISABLE = 0,
    GPIO_PULLUP_ENABLE  = 1
} GPIO_Pullup_t;

/* Pin configuration used by GPIO_Init() */
typedef struct {
    GPIO_Port_t       port;
    uint8_t           pinMask;        /* bit mask: 0x01, 0x02, ..., 0xFF */
    GPIO_Direction_t  direction;
    GPIO_Level_t      initialLevel;
    GPIO_Pullup_t     pullup;
} GPIO_PinConfig_t;

/* External interrupt edge/trigger selection */
typedef enum {
    GPIO_INT_TRIGGER_LOW      = 0,    /* INT0..INT7 only */
    GPIO_INT_TRIGGER_CHANGE   = 1,    /* INT0..INT7 only */
    GPIO_INT_TRIGGER_FALLING  = 2,
    GPIO_INT_TRIGGER_RISING   = 3
} GPIO_IntTrigger_t;

/* External interrupt source (INT0..INT7) */
typedef enum {
    GPIO_EXT_INT0 = 0,
    GPIO_EXT_INT1,
    GPIO_EXT_INT2,
    GPIO_EXT_INT3,
    GPIO_EXT_INT4,
    GPIO_EXT_INT5,
    GPIO_EXT_INT6,
    GPIO_EXT_INT7
} GPIO_ExtInt_t;

/* Pin-change interrupt bank (each bank covers a group of pins) */
typedef enum {
    GPIO_PCINT_BANK0 = 0,    /* PCINT0..7   -> mostly PORTA */
    GPIO_PCINT_BANK1,        /* PCINT8..15  -> mostly PORTB */
    GPIO_PCINT_BANK2,        /* PCINT16..23 -> mostly PORTC */
    GPIO_PCINT_BANK3         /* PCINT24..31 -> mostly PORTE on ATmega2560 */
} GPIO_PcintBank_t;

/* Generic ISR callback type (no arguments, no return) */
typedef void (*GPIO_Callback_t)(void);

/* ============================================================
 * GPIO API - basic digital I/O
 * ============================================================ */

/**
 * Configure one or more pins of a port.
 * @param cfg  pointer to configuration; cfg->pinMask selects bits.
 */
void GPIO_Init(const GPIO_PinConfig_t *cfg);

/**
 * Set direction for the selected pins of the given port.
 */
void GPIO_SetDirection(GPIO_Port_t port,
                       uint8_t pinMask,
                       GPIO_Direction_t dir);

/**
 * Write the level of the selected pins (does not affect other pins).
 * For input pins the level is stored in PORT (controls pull-up when
 * DDR=0 and PU enabled).
 */
void GPIO_Write(GPIO_Port_t port, uint8_t pinMask, GPIO_Level_t level);

/**
 * Convenience: drive all selected pins HIGH.
 */
void GPIO_SetPins(GPIO_Port_t port, uint8_t pinMask);

/**
 * Convenience: drive all selected pins LOW.
 */
void GPIO_ClearPins(GPIO_Port_t port, uint8_t pinMask);

/**
 * Toggle all selected pins.
 */
void GPIO_TogglePins(GPIO_Port_t port, uint8_t pinMask);

/**
 * Read the level of all selected pins (non-zero -> HIGH, 0 -> LOW).
 */
GPIO_Level_t GPIO_ReadPins(GPIO_Port_t port, uint8_t pinMask);

/**
 * Read full port pin register.
 */
uint8_t GPIO_ReadPort(GPIO_Port_t port);

/**
 * Enable internal pull-up for selected pins. The pins must be inputs.
 */
void GPIO_EnablePullup(GPIO_Port_t port, uint8_t pinMask);

/**
 * Disable internal pull-up for selected pins.
 */
void GPIO_DisablePullup(GPIO_Port_t port, uint8_t pinMask);

/* ============================================================
 * Global interrupt helpers (atomic section / sei() / cli())
 * ============================================================ */

/**
 * Atomically set a value of an 8-bit port register.
 * Disables interrupts while writing.
 */
void GPIO_AtomicWrite(volatile uint8_t *reg, uint8_t value);

/**
 * Enable global interrupts (sei()).
 */
void GPIO_GlobalInterruptEnable(void);

/**
 * Disable global interrupts (cli()).
 */
void GPIO_GlobalInterruptDisable(void);

/* ============================================================
 * External interrupt API (INT0..INT7)
 * ============================================================ */

/**
 * Configure an external interrupt.
 * @param extInt  one of GPIO_EXT_INT0..GPIO_EXT_INT7
 * @param trigger edge/level trigger
 * @param cb      user callback invoked from the ISR (may be NULL).
 *                If NULL the user is expected to provide a custom ISR.
 */
void GPIO_ExtIntConfigure(GPIO_ExtInt_t extInt,
                          GPIO_IntTrigger_t trigger,
                          GPIO_Callback_t cb);

/**
 * Enable the selected external interrupt in software (in addition to
 * the global I flag which is also required for the ISR to fire).
 */
void GPIO_ExtIntEnable(GPIO_ExtInt_t extInt);

/**
 * Disable the selected external interrupt.
 */
void GPIO_ExtIntDisable(GPIO_ExtInt_t extInt);

/**
 * Clear the interrupt flag (write 1 to clear - datasheet convention).
 */
void GPIO_ExtIntClearFlag(GPIO_ExtInt_t extInt);

/* ============================================================
 * Pin-change interrupt API (PCINT0..PCINT23 on ATmega2560)
 * ============================================================ */

/**
 * Configure a pin-change interrupt.
 * @param bank   one of GPIO_PCINT_BANK0..BANK3
 * @param pinMask  selects which pins in the bank to enable (e.g. 0x03
 *                  to enable PCINT0 and PCINT1 inside BANK0).
 * @param cb     user callback (called with the bank as parameter via
 *               GPIO_PcintBankCallback_t, see below).
 */
typedef void (*GPIO_PcintCallback_t)(GPIO_PcintBank_t bank);

void GPIO_PcintConfigure(GPIO_PcintBank_t bank,
                         uint8_t pinMask,
                         GPIO_PcintCallback_t cb);

void GPIO_PcintEnable(GPIO_PcintBank_t bank);
void GPIO_PcintDisable(GPIO_PcintBank_t bank);
void GPIO_PcintClearFlag(GPIO_PcintBank_t bank);

#ifdef __cplusplus
}
#endif

#endif /* GPIOM2560_H_ */
