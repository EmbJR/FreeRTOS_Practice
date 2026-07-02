#ifndef TIMERM2560_H_
#define TIMERM2560_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * Bare-metal Timer/Counter driver for ATmega2560
 * - Supports Timer0 (8-bit), Timer1/3/4/5 (16-bit), Timer2 (8-bit, async)
 * - Modes: Normal, CTC, Fast PWM, Phase Correct PWM, Phase & Frequency Correct PWM (16-bit)
 * - Interrupt support with user-defined callbacks
 *
 * Reference: ATmega640/1280/1281/2560/2561 Datasheet (Atmel-2549)
 *            Sections 15 (8-bit T/C0), 16 (16-bit T/C1,3,4,5), 17 (8-bit T/C2)
 */

#define F_CPU 16000000UL

/* Timer module identifiers */
typedef enum {
    TIMER0 = 0,
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3,
    TIMER4 = 4,
    TIMER5 = 5
} Timer_t;

/* Timer widths */
typedef enum {
    TIMER_8BIT  = 8,
    TIMER_16BIT = 16
} TimerWidth_t;

/* Waveform Generation Modes (WGM) - numeric value matches WGM[2:0] register encoding */
typedef enum {
    TIMER_MODE_NORMAL                       = 0,
    TIMER_MODE_PWM_PHASE_CORRECT_8BIT       = 1,   /* 8-bit  : TOP=0xFF   */
    TIMER_MODE_PWM_PHASE_CORRECT_9BIT       = 2,   /* 16-bit : TOP=0x1FF  */
    TIMER_MODE_PWM_PHASE_CORRECT_10BIT      = 3,   /* 16-bit : TOP=0x3FF  */
    TIMER_MODE_CTC                          = 4,   /* 8/16-bit: TOP=OCRA  */
    TIMER_MODE_PWM_FAST_8BIT                = 5,   /* 8-bit  : TOP=0xFF   */
    TIMER_MODE_PWM_FAST_9BIT                = 6,   /* 16-bit : TOP=0x1FF  */
    TIMER_MODE_PWM_FAST_10BIT               = 7,   /* 16-bit : TOP=0x3FF  */
    TIMER_MODE_PWM_PHASE_FREQ_CORRECT_ICR   = 8,   /* 16-bit : TOP=ICR   */
    TIMER_MODE_PWM_PHASE_FREQ_CORRECT_OCR   = 9,   /* 16-bit : TOP=OCRA  */
    TIMER_MODE_PWM_PHASE_CORRECT_ICR        = 10,  /* 16-bit : TOP=ICR   */
    TIMER_MODE_PWM_PHASE_CORRECT_OCR        = 11,  /* 16-bit : TOP=OCRA  */
    TIMER_MODE_CTC_ICR                      = 12,  /* 16-bit : TOP=ICR   */
    TIMER_MODE_RESERVED_13                  = 13,
    TIMER_MODE_PWM_FAST_ICR                 = 14,  /* 16-bit : TOP=ICR   */
    TIMER_MODE_PWM_FAST_OCR                 = 15   /* 16-bit : TOP=OCRA  */
} TimerMode_t;

/* Clock prescaler values (CS bits) */
typedef enum {
    TIMER_PRESCALER_STOP   = 0,
    TIMER_PRESCALER_1      = 1,
    TIMER_PRESCALER_8      = 2,
    TIMER_PRESCALER_32     = 3,   /* 8-bit Timer0/2 only */
    TIMER_PRESCALER_64     = 4,
    TIMER_PRESCALER_128    = 5,   /* 8-bit Timer0/2 only */
    TIMER_PRESCALER_256    = 6,
    TIMER_PRESCALER_1024   = 7,
    /* External clock on Tn pin, falling edge */
    TIMER_EXT_FALLING      = 6,
    /* External clock on Tn pin, rising edge */
    TIMER_EXT_RISING       = 7
} TimerPrescaler_t;

/* Compare Output Mode (COM bits) for channel A/B */
typedef enum {
    TIMER_OC_DISCONNECTED = 0,   /* Normal port operation           */
    TIMER_OC_TOGGLE       = 1,   /* Toggle on compare match (non-PWM)*/
    TIMER_OC_CLEAR        = 2,   /* Clear on compare (non-inv PWM)  */
    TIMER_OC_SET          = 3    /* Set on compare (inv PWM)        */
} TimerOCMode_t;

/* Interrupt source selection */
typedef enum {
    TIMER_INT_OVERFLOW = 0,  /* TOIEn (overflow)                */
    TIMER_INT_COMPA    = 1,  /* OCIEnA (Output Compare A match) */
    TIMER_INT_COMPB    = 2,  /* OCIEnB (Output Compare B match) */
    TIMER_INT_COMPC    = 3   /* OCIEnC (16-bit timers only)     */
} TimerIntSrc_t;

/* Callback function type */
typedef void (*TimerCallback_t)(void);

/* Driver configuration structure */
typedef struct {
    Timer_t           timer;
    TimerMode_t       mode;
    TimerPrescaler_t  prescaler;
    TimerWidth_t      width;   /* informational; derived from timer id */
} TimerConfig_t;

/* ---- API ---- */

/* Initialise and start a timer with the given configuration */
void Timer_Init(const TimerConfig_t *cfg);

/* Stop the timer (CS bits = 0) */
void Timer_Stop(Timer_t timer);

/* Start the timer with previously configured prescaler */
void Timer_Start(Timer_t timer);

/* Write a counter value */
void Timer_SetCounter(Timer_t timer, uint16_t value);
uint16_t Timer_GetCounter(Timer_t timer);

/* Write a Compare value to channel A/B/C (16-bit timers only support C) */
void Timer_SetCompareA(Timer_t timer, uint16_t value);
void Timer_SetCompareB(Timer_t timer, uint16_t value);
void Timer_SetCompareC(Timer_t timer, uint16_t value);

/* Configure Output Compare pin behaviour for channel A/B */
void Timer_SetOutputCompareA(Timer_t timer, TimerOCMode_t mode);
void Timer_SetOutputCompareB(Timer_t timer, TimerOCMode_t mode);

/* Set TOP via Input Capture Register (16-bit timers) */
void Timer_SetICR(Timer_t timer, uint16_t value);

/* Force Output Compare on channel A/B (strobe bit) */
void Timer_ForceCompareA(Timer_t timer);
void Timer_ForceCompareB(Timer_t timer);

/* Interrupt control */
void Timer_EnableInterrupt(Timer_t timer, TimerIntSrc_t src);
void Timer_DisableInterrupt(Timer_t timer, TimerIntSrc_t src);

/* Register user callback (called from ISR). Pass NULL to clear. */
void Timer_RegisterCallback(Timer_t timer, TimerIntSrc_t src, TimerCallback_t cb);

/* Read & clear interrupt flag (returns 1 if flag was set) */
uint8_t Timer_GetFlag(Timer_t timer, TimerIntSrc_t src);
void    Timer_ClearFlag(Timer_t timer, TimerIntSrc_t src);

/* Global enable/disable of timer interrupts (used by ISR dispatcher) */
void Timer_GlobalIrqEnable(void);
void Timer_GlobalIrqDisable(void);

/* ---- Convenience helpers ---- */

/* Compute prescaler / TOP value (16-bit) for a desired period (in microseconds).
 * Returns true on success. out_prescaler and out_top receive the values.
 * If the requested period cannot be achieved, returns false and the closest
 * achievable period is reported via *actual_period_us (if non-NULL).
 */
bool Timer_ComputePeriod16(TimerMode_t mode, uint32_t period_us,
                           TimerPrescaler_t *out_prescaler,
                           uint16_t *out_top,
                           uint32_t *actual_period_us);

/* Same for 8-bit timers */
bool Timer_ComputePeriod8(TimerMode_t mode, uint32_t period_us,
                          TimerPrescaler_t *out_prescaler,
                          uint16_t *out_top,
                          uint32_t *actual_period_us);

#endif /* TIMERM2560_H_ */
