/*
 * example_gpio_interrupt.c
 *
 * Bare-metal GPIO + external-interrupt example for ATmega2560
 * using the gpiom2560 driver.
 *
 * Demonstrates:
 *   - INT5 on PE5 (Arduino MEGA pin 3) handling a button press.
 *   - PCI on PCINT0 (PA0 / digital pin 22) handling a second source.
 *   - LED toggled from each ISR (each ISR toggles its own LED).
 *
 * Both ISRs run with global interrupts enabled (sei()), so the CPU
 * can sleep in main() between events.
 */

#include <avr/sleep.h>
#include "gpiom2560.h"

/* LEDs on PH5 and PH6 */
#define LED1_PORT     GPIO_PORT_H
#define LED1_MASK     (1u << 5)
#define LED2_PORT     GPIO_PORT_H
#define LED2_MASK     (1u << 6)

/* External interrupt button on PE5 = INT5 */
#define EXTINT_BUTTON_PORT  GPIO_PORT_E
#define EXTINT_BUTTON_MASK  (1u << 5)
#define EXTINT_BUTTON_NUM   GPIO_EXT_INT5

/* Pin-change interrupt button on PA0 = PCINT0 */
#define PCINT_BUTTON_PORT   GPIO_PORT_A
#define PCINT_BUTTON_MASK   (1u << 0)
#define PCINT_BUTTON_BANK   GPIO_PCINT_BANK0

/* --------------- ISRs / callbacks --------------- */

static void on_int5_press(void)
{
    GPIO_TogglePins(LED1_PORT, LED1_MASK);
}

static void on_pcint0_press(GPIO_PcintBank_t bank)
{
    (void)bank;
    GPIO_TogglePins(LED2_PORT, LED2_MASK);
}

/* --------------- Configuration helpers --------------- */

static void board_io_init(void)
{
    GPIO_PinConfig_t cfg;

    cfg.port          = LED1_PORT;
    cfg.pinMask       = LED1_MASK;
    cfg.direction     = GPIO_DIR_OUTPUT;
    cfg.initialLevel  = GPIO_LEVEL_LOW;
    cfg.pullup        = GPIO_PULLUP_DISABLE;
    GPIO_Init(&cfg);

    cfg.port          = LED2_PORT;
    cfg.pinMask       = LED2_MASK;
    GPIO_Init(&cfg);

    /* External interrupt button (active low with internal pull-up) */
    cfg.port          = EXTINT_BUTTON_PORT;
    cfg.pinMask       = EXTINT_BUTTON_MASK;
    cfg.direction     = GPIO_DIR_INPUT;
    cfg.initialLevel  = GPIO_LEVEL_LOW;
    cfg.pullup        = GPIO_PULLUP_ENABLE;
    GPIO_Init(&cfg);

    /* Pin-change interrupt button (active low with internal pull-up) */
    cfg.port          = PCINT_BUTTON_PORT;
    cfg.pinMask       = PCINT_BUTTON_MASK;
    GPIO_Init(&cfg);

    /* Wire up interrupts */
    GPIO_ExtIntConfigure(EXTINT_BUTTON_NUM,
                         GPIO_INT_TRIGGER_FALLING,
                         on_int5_press);

    GPIO_PcintConfigure(PCINT_BUTTON_BANK,
                        PCINT_BUTTON_MASK,
                        on_pcint0_press);

    GPIO_ExtIntEnable(EXTINT_BUTTON_NUM);
    GPIO_PcintEnable(PCINT_BUTTON_BANK);

    GPIO_GlobalInterruptEnable();
}

int main(void)
{
    board_io_init();

    /* Go to sleep between events to demonstrate ISR-driven operation. */
    set_sleep_mode(SLEEP_MODE_IDLE);
    while (1) {
        sleep_mode();
    }
}
