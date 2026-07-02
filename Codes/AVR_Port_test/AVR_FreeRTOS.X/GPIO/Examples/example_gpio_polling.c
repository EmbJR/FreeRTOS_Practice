/*
 * example_gpio_polling.c
 *
 * Bare-metal GPIO example for ATmega2560 using gpiom2560 driver.
 * Polls a button and toggles an LED without using any interrupts.
 *
 * Wiring (example on ATmega2560):
 *   - LED    -> PH5 (Arduino MEGA pin 9) on PORTB pin 4 area? Actually PH5 is D9.
 *              We just need one GPIO - using PORTH pin 5 (PH5).
 *   - Button -> PIND2 (Arduino MEGA pin 50)
 *
 * Behaviour:
 *   - Press the button -> LED toggles.
 *   - Software debounce via simple counter.
 */

#include <util/delay.h>
#include "gpiom2560.h"

#define LED_PORT      GPIO_PORT_H
#define LED_MASK      (1u << 5)              /* PH5 */
#define BUTTON_PORT   GPIO_PORT_D
#define BUTTON_MASK   (1u << 2)              /* PD2 */

static void button_setup(void)
{
    GPIO_PinConfig_t btn = {
        .port          = BUTTON_PORT,
        .pinMask       = BUTTON_MASK,
        .direction     = GPIO_DIR_INPUT,
        .initialLevel  = GPIO_LEVEL_LOW,
        .pullup        = GPIO_PULLUP_ENABLE   /* active-low button */
    };
    GPIO_Init(&btn);
}

static void led_setup(void)
{
    GPIO_PinConfig_t led = {
        .port          = LED_PORT,
        .pinMask       = LED_MASK,
        .direction     = GPIO_DIR_OUTPUT,
        .initialLevel  = GPIO_LEVEL_LOW,
        .pullup        = GPIO_PULLUP_DISABLE
    };
    GPIO_Init(&led);
}

int main(void)
{
    led_setup();
    button_setup();

    GPIO_Level_t prev = GPIO_LEVEL_HIGH;   /* idle state: pull-up */
    GPIO_Level_t curr;

    while (1) {
        curr = GPIO_ReadPins(BUTTON_PORT, BUTTON_MASK);

        if (prev == GPIO_LEVEL_HIGH && curr == GPIO_LEVEL_LOW) {
            /* button just pressed -> toggle LED */
            GPIO_TogglePins(LED_PORT, LED_MASK);
            _delay_ms(50);                  /* simple debounce */
        }
        prev = curr;
        _delay_ms(10);
    }
}
