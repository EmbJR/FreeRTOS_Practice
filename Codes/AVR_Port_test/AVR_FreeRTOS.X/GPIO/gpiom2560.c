/*
 * gpiom2560.c
 *
 * Bare-metal GPIO + interrupt driver for ATmega2560 (AVR-GCC).
 * See gpiom2560.h for usage.
 */

#include "gpiom2560.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

/* ============================================================
 * Module-private helpers
 * ============================================================ */

static volatile uint8_t *gpio_port_reg(GPIO_Port_t port)
{
    switch (port) {
    case GPIO_PORT_A: return GPIO_PORTA;
    case GPIO_PORT_B: return GPIO_PORTB;
    case GPIO_PORT_C: return GPIO_PORTC;
    case GPIO_PORT_D: return GPIO_PORTD;
    case GPIO_PORT_E: return GPIO_PORTE;
    case GPIO_PORT_F: return GPIO_PORTF;
    case GPIO_PORT_G: return GPIO_PORTG;
    case GPIO_PORT_H: return GPIO_PORTH;
    case GPIO_PORT_J: return GPIO_PORTJ;
    case GPIO_PORT_K: return GPIO_PORTK;
    case GPIO_PORT_L: return GPIO_PORTL;
    default:          return (volatile uint8_t *)0;
    }
}

static volatile uint8_t *gpio_ddr_reg(GPIO_Port_t port)
{
    switch (port) {
    case GPIO_PORT_A: return GPIO_DDRA;
    case GPIO_PORT_B: return GPIO_DDRB;
    case GPIO_PORT_C: return GPIO_DDRC;
    case GPIO_PORT_D: return GPIO_DDRD;
    case GPIO_PORT_E: return GPIO_DDRE;
    case GPIO_PORT_F: return GPIO_DDRF;
    case GPIO_PORT_G: return GPIO_DDRG;
    case GPIO_PORT_H: return GPIO_DDRH;
    case GPIO_PORT_J: return GPIO_DDRJ;
    case GPIO_PORT_K: return GPIO_DDRK;
    case GPIO_PORT_L: return GPIO_DDRL;
    default:          return (volatile uint8_t *)0;
    }
}

static volatile uint8_t *gpio_pin_reg(GPIO_Port_t port)
{
    switch (port) {
    case GPIO_PORT_A: return GPIO_PINA;
    case GPIO_PORT_B: return GPIO_PINB;
    case GPIO_PORT_C: return GPIO_PINC;
    case GPIO_PORT_D: return GPIO_PIND;
    case GPIO_PORT_E: return GPIO_PINE;
    case GPIO_PORT_F: return GPIO_PINF;
    case GPIO_PORT_G: return GPIO_PING;
    case GPIO_PORT_H: return GPIO_PINH;
    case GPIO_PORT_J: return GPIO_PINJ;
    case GPIO_PORT_K: return GPIO_PINK;
    case GPIO_PORT_L: return GPIO_PINL;
    default:          return (volatile uint8_t *)0;
    }
}

/* ============================================================
 * GPIO API - basic digital I/O
 * ============================================================ */

void GPIO_Init(const GPIO_PinConfig_t *cfg)
{
    if (cfg == 0) {
        return;
    }

    volatile uint8_t *ddr  = gpio_ddr_reg(cfg->port);
    volatile uint8_t *port = gpio_port_reg(cfg->port);

    if (ddr == 0 || port == 0) {
        return;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (cfg->direction == GPIO_DIR_OUTPUT) {
            *ddr  |=  cfg->pinMask;          /* pin as output       */
            if (cfg->initialLevel == GPIO_LEVEL_HIGH) {
                *port |=  cfg->pinMask;
            } else {
                *port &= (uint8_t)~cfg->pinMask;
            }
        } else {
            *ddr &= (uint8_t)~cfg->pinMask;  /* pin as input        */
            if (cfg->pullup == GPIO_PULLUP_ENABLE) {
                *port |=  cfg->pinMask;      /* enable pull-up      */
            } else {
                *port &= (uint8_t)~cfg->pinMask;
            }
        }
    }
}

void GPIO_SetDirection(GPIO_Port_t port, uint8_t pinMask, GPIO_Direction_t dir)
{
    volatile uint8_t *ddr = gpio_ddr_reg(port);
    if (ddr == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (dir == GPIO_DIR_OUTPUT) {
            *ddr |=  pinMask;
        } else {
            *ddr &= (uint8_t)~pinMask;
        }
    }
}

void GPIO_Write(GPIO_Port_t port, uint8_t pinMask, GPIO_Level_t level)
{
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (level == GPIO_LEVEL_HIGH) {
            *portReg |=  pinMask;
        } else {
            *portReg &= (uint8_t)~pinMask;
        }
    }
}

void GPIO_SetPins(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *portReg |= pinMask;
    }
}

void GPIO_ClearPins(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *portReg &= (uint8_t)~pinMask;
    }
}

void GPIO_TogglePins(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *portReg ^= pinMask;
    }
}

GPIO_Level_t GPIO_ReadPins(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *pinReg = gpio_pin_reg(port);
    if (pinReg == 0 || pinMask == 0) {
        return GPIO_LEVEL_LOW;
    }
    return ((*pinReg & pinMask) != 0u) ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW;
}

uint8_t GPIO_ReadPort(GPIO_Port_t port)
{
    volatile uint8_t *pinReg = gpio_pin_reg(port);
    if (pinReg == 0) {
        return 0u;
    }
    return *pinReg;
}

void GPIO_EnablePullup(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *ddr  = gpio_ddr_reg(port);
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (ddr == 0 || portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *ddr     &= (uint8_t)~pinMask;   /* make sure it is an input */
        *portReg |=  pinMask;            /* enable pull-up           */
    }
}

void GPIO_DisablePullup(GPIO_Port_t port, uint8_t pinMask)
{
    volatile uint8_t *portReg = gpio_port_reg(port);
    if (portReg == 0) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *portReg &= (uint8_t)~pinMask;
    }
}

/* ============================================================
 * Atomic / global interrupt helpers
 * ============================================================ */

void GPIO_AtomicWrite(volatile uint8_t *reg, uint8_t value)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *reg = value;
    }
}

void GPIO_GlobalInterruptEnable(void)
{
    sei();
}

void GPIO_GlobalInterruptDisable(void)
{
    cli();
}

/* ============================================================
 * External interrupts (INT0..INT7)
 * ============================================================ */

/* Per-vector callback table */
static GPIO_Callback_t extIntCallbacks[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static void extint_program_eicra_bits(GPIO_ExtInt_t extInt, GPIO_IntTrigger_t trig)
{
    /* INT0..INT3 are placed in EICRA (ISCn1:ISCn0), INT4..INT7 in EICRB. */
    uint8_t bits = (uint8_t)trig & 0x03u;
    uint8_t shift;

    if (extInt <= GPIO_EXT_INT3) {
        shift = (uint8_t)extInt * 2u;
        EXTINT_EICRA = (uint8_t)((EXTINT_EICRA & (uint8_t)~((uint8_t)0x03u << shift))
                                 | (bits << shift));
    } else {
        shift = ((uint8_t)extInt - 4u) * 2u;
        EXTINT_EICRB = (uint8_t)((EXTINT_EICRB & (uint8_t)~((uint8_t)0x03u << shift))
                                 | (bits << shift));
    }
}

void GPIO_ExtIntConfigure(GPIO_ExtInt_t extInt,
                          GPIO_IntTrigger_t trigger,
                          GPIO_Callback_t cb)
{
    if ((uint8_t)extInt > (uint8_t)GPIO_EXT_INT7) {
        return;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        extint_program_eicra_bits(extInt, trigger);
        /* Make sure the flag is cleared before enabling */
        EXTINT_EIFR = (uint8_t)((uint8_t)1u << (uint8_t)extInt);
        extIntCallbacks[extInt] = cb;
    }
}

void GPIO_ExtIntEnable(GPIO_ExtInt_t extInt)
{
    if ((uint8_t)extInt > (uint8_t)GPIO_EXT_INT7) {
        return;
    }
    EXTINT_EIMSK |= (uint8_t)((uint8_t)1u << (uint8_t)extInt);
}

void GPIO_ExtIntDisable(GPIO_ExtInt_t extInt)
{
    if ((uint8_t)extInt > (uint8_t)GPIO_EXT_INT7) {
        return;
    }
    EXTINT_EIMSK &= (uint8_t)~((uint8_t)1u << (uint8_t)extInt);
}

void GPIO_ExtIntClearFlag(GPIO_ExtInt_t extInt)
{
    if ((uint8_t)extInt > (uint8_t)GPIO_EXT_INT7) {
        return;
    }
    EXTINT_EIFR = (uint8_t)((uint8_t)1u << (uint8_t)extInt);  /* write 1 to clear */
}

/* ---- ISRs ----------------------------------------------------------- */

ISR(INT0_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT0); if (extIntCallbacks[0]) extIntCallbacks[0](); }
ISR(INT1_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT1); if (extIntCallbacks[1]) extIntCallbacks[1](); }
ISR(INT2_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT2); if (extIntCallbacks[2]) extIntCallbacks[2](); }
ISR(INT3_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT3); if (extIntCallbacks[3]) extIntCallbacks[3](); }
ISR(INT4_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT4); if (extIntCallbacks[4]) extIntCallbacks[4](); }
ISR(INT5_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT5); if (extIntCallbacks[5]) extIntCallbacks[5](); }
ISR(INT6_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT6); if (extIntCallbacks[6]) extIntCallbacks[6](); }
ISR(INT7_vect)  { GPIO_ExtIntClearFlag(GPIO_EXT_INT7); if (extIntCallbacks[7]) extIntCallbacks[7](); }

/* ============================================================
 * Pin-change interrupts
 * ============================================================ */

/* One callback per bank */
static GPIO_PcintCallback_t pcintCallbacks[4] = { 0, 0, 0, 0 };

static volatile uint8_t *pcint_msk_reg(GPIO_PcintBank_t bank)
{
    switch (bank) {
    case GPIO_PCINT_BANK0: return &EXTINT_PCMSK0;
    case GPIO_PCINT_BANK1: return &EXTINT_PCMSK1;
    case GPIO_PCINT_BANK2: return &EXTINT_PCMSK2;
    case GPIO_PCINT_BANK3: return &EXTINT_PCMSK3;
    default:               return (volatile uint8_t *)0;
    }
}

static uint8_t pcint_flag_bit(GPIO_PcintBank_t bank)
{
    /* Bit position in PCIFR is identical to the bank index (PCIF0..PCIF3) */
    return (uint8_t)bank;
}

void GPIO_PcintConfigure(GPIO_PcintBank_t bank,
                         uint8_t pinMask,
                         GPIO_PcintCallback_t cb)
{
    volatile uint8_t *msk = pcint_msk_reg(bank);
    if (msk == 0) {
        return;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *msk = pinMask;                                /* enables individual PCINTs */
        EXTINT_PCIFR = (uint8_t)((uint8_t)1u << pcint_flag_bit(bank)); /* clear flag */
        pcintCallbacks[bank] = cb;
    }
}

void GPIO_PcintEnable(GPIO_PcintBank_t bank)
{
    if ((uint8_t)bank > (uint8_t)GPIO_PCINT_BANK3) {
        return;
    }
    EXTINT_PCICR |= (uint8_t)((uint8_t)1u << (uint8_t)bank);
}

void GPIO_PcintDisable(GPIO_PcintBank_t bank)
{
    if ((uint8_t)bank > (uint8_t)GPIO_PCINT_BANK3) {
        return;
    }
    EXTINT_PCICR &= (uint8_t)~((uint8_t)1u << (uint8_t)bank);
}

void GPIO_PcintClearFlag(GPIO_PcintBank_t bank)
{
    if ((uint8_t)bank > (uint8_t)GPIO_PCINT_BANK3) {
        return;
    }
    EXTINT_PCIFR = (uint8_t)((uint8_t)1u << pcint_flag_bit(bank));
}

/* ---- ISRs ----------------------------------------------------------- */

ISR(PCINT0_vect) {
    GPIO_PcintClearFlag(GPIO_PCINT_BANK0);
    if (pcintCallbacks[0]) pcintCallbacks[0](GPIO_PCINT_BANK0);
}
ISR(PCINT1_vect) {
    GPIO_PcintClearFlag(GPIO_PCINT_BANK1);
    if (pcintCallbacks[1]) pcintCallbacks[1](GPIO_PCINT_BANK1);
}
ISR(PCINT2_vect) {
    GPIO_PcintClearFlag(GPIO_PCINT_BANK2);
    if (pcintCallbacks[2]) pcintCallbacks[2](GPIO_PCINT_BANK2);
}
ISR(PCINT3_vect) {
    GPIO_PcintClearFlag(GPIO_PCINT_BANK3);
    if (pcintCallbacks[3]) pcintCallbacks[3](GPIO_PCINT_BANK3);
}
