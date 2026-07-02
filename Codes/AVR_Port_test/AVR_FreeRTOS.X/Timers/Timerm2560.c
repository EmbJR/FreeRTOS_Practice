/*
 * Timerm2560.c - Bare-metal Timer/Counter driver for ATmega2560
 *
 * Reference: ATmega640/1280/1281/2560/2561 Datasheet (Atmel-2549)
 *   - Section 15 : 8-bit Timer/Counter0
 *   - Section 16 : 16-bit Timer/Counter1,3,4,5
 *   - Section 17 : 8-bit Timer/Counter2 (with async)
 */

#include "Timerm2560.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

/* Callback table indexed by (timer, source) */
static TimerCallback_t s_callbacks[6][4] = { {0} };
static uint8_t s_prescalers[6] = { 0 };

/* Forward declarations for register access helpers used by the WGM helper. */
static inline volatile uint8_t *tccra_reg(Timer_t t);
static inline volatile uint8_t *tccrb_reg(Timer_t t);
static inline uint8_t width_of(Timer_t t);

/* ---- WGM bit helpers ----
 * The public enum values are defined for the 16-bit timer WGM encoding, but
 * 8-bit timers only use the 3-bit pattern 000/001/010/011.  We translate the
 * requested mode into the AVR register bits depending on the timer width.
 */
static inline uint8_t mode_to_wgm_bits(Timer_t t, TimerMode_t mode)
{
    if (width_of(t) == 16) {
        uint8_t mode_value = (uint8_t)mode;
        if (mode_value > 15) mode_value = 0;
        return mode_value;
    }

    switch (mode) {
        case TIMER_MODE_NORMAL:               return 0x00;
        case TIMER_MODE_PWM_PHASE_CORRECT_8BIT: return 0x01;
        case TIMER_MODE_CTC:                  return 0x02;
        case TIMER_MODE_PWM_FAST_8BIT:        return 0x03;
        default:                              return 0x00;
    }
}

static inline void apply_wgm_bits(Timer_t t, TimerMode_t mode)
{
    volatile uint8_t *tccra = tccra_reg(t);
    volatile uint8_t *tccrb = tccrb_reg(t);
    if (!tccra || !tccrb) return;

    uint8_t wgm = mode_to_wgm_bits(t, mode);
    uint8_t wgm0_1 = (uint8_t)(wgm & 0x03);
    uint8_t wgm2   = (uint8_t)((wgm >> 2) & 0x01);
    uint8_t wgm3   = (uint8_t)((wgm >> 3) & 0x01);

    *tccra = (uint8_t)((*tccra & ~((1u << WGM00) | (1u << WGM01))) |
                       (wgm0_1 << WGM00));

    if (width_of(t) == 16) {
        *tccrb = (uint8_t)((*tccrb & ~((1u << WGM12) | (1u << WGM13))) |
                           ((wgm2 << WGM12) | (wgm3 << WGM13)));
    } else {
        *tccrb = (uint8_t)((*tccrb & ~((1u << WGM02))) |
                           (wgm2 << WGM02));
    }
}

/* ---- Bit-name helpers ----
 * The AVR device header provides bit names with the timer number baked in
 * (COM0A1, COM1A1, COM3A1, ...).  We map Timer_t -> timer number and
 * use the per-number macros.
 */

/* ---- Register accessors (return 16-bit as low-byte pointer + high-byte pointer) ---- */

static inline volatile uint8_t *tcnt_lo(Timer_t t) {
    switch (t) {
        case TIMER0: return &TCNT0;
        case TIMER1: return &TCNT1L;
        case TIMER2: return &TCNT2;
        case TIMER3: return &TCNT3L;
        case TIMER4: return &TCNT4L;
        case TIMER5: return &TCNT5L;
    }
    return 0;
}
static inline volatile uint8_t *tcnt_hi(Timer_t t) {
    switch (t) {
        case TIMER1: return &TCNT1H;
        case TIMER3: return &TCNT3H;
        case TIMER4: return &TCNT4H;
        case TIMER5: return &TCNT5H;
    }
    return 0;
}

static inline volatile uint8_t *ocra_lo(Timer_t t) {
    switch (t) {
        case TIMER0: return &OCR0A;
        case TIMER1: return &OCR1AL;
        case TIMER2: return &OCR2A;
        case TIMER3: return &OCR3AL;
        case TIMER4: return &OCR4AL;
        case TIMER5: return &OCR5AL;
    }
    return 0;
}
static inline volatile uint8_t *ocra_hi(Timer_t t) {
    switch (t) {
        case TIMER1: return &OCR1AH;
        case TIMER3: return &OCR3AH;
        case TIMER4: return &OCR4AH;
        case TIMER5: return &OCR5AH;
    }
    return 0;
}

static inline volatile uint8_t *ocrb_lo(Timer_t t) {
    switch (t) {
        case TIMER0: return &OCR0B;
        case TIMER1: return &OCR1BL;
        case TIMER2: return &OCR2B;
        case TIMER3: return &OCR3BL;
        case TIMER4: return &OCR4BL;
        case TIMER5: return &OCR5BL;
    }
    return 0;
}
static inline volatile uint8_t *ocrb_hi(Timer_t t) {
    switch (t) {
        case TIMER1: return &OCR1BH;
        case TIMER3: return &OCR3BH;
        case TIMER4: return &OCR4BH;
        case TIMER5: return &OCR5BH;
    }
    return 0;
}

static inline volatile uint8_t *ocrc_lo(Timer_t t) {
    switch (t) {
        case TIMER1: return &OCR1CL;
        case TIMER3: return &OCR3CL;
        case TIMER4: return &OCR4CL;
        case TIMER5: return &OCR5CL;
        default:    return 0;
    }
}
static inline volatile uint8_t *ocrc_hi(Timer_t t) {
    switch (t) {
        case TIMER1: return &OCR1CH;
        case TIMER3: return &OCR3CH;
        case TIMER4: return &OCR4CH;
        case TIMER5: return &OCR5CH;
        default:    return 0;
    }
}

static inline volatile uint8_t *icr_lo(Timer_t t) {
    switch (t) {
        case TIMER1: return &ICR1L;
        case TIMER3: return &ICR3L;
        case TIMER4: return &ICR4L;
        case TIMER5: return &ICR5L;
        default:    return 0;
    }
}
static inline volatile uint8_t *icr_hi(Timer_t t) {
    switch (t) {
        case TIMER1: return &ICR1H;
        case TIMER3: return &ICR3H;
        case TIMER4: return &ICR4H;
        case TIMER5: return &ICR5H;
        default:    return 0;
    }
}

static inline volatile uint8_t *tccra_reg(Timer_t t) {
    switch (t) {
        case TIMER0: return &TCCR0A;
        case TIMER1: return &TCCR1A;
        case TIMER2: return &TCCR2A;
        case TIMER3: return &TCCR3A;
        case TIMER4: return &TCCR4A;
        case TIMER5: return &TCCR5A;
    }
    return 0;
}
static inline volatile uint8_t *tccrb_reg(Timer_t t) {
    switch (t) {
        case TIMER0: return &TCCR0B;
        case TIMER1: return &TCCR1B;
        case TIMER2: return &TCCR2B;
        case TIMER3: return &TCCR3B;
        case TIMER4: return &TCCR4B;
        case TIMER5: return &TCCR5B;
    }
    return 0;
}
static inline volatile uint8_t *tccrc_reg(Timer_t t) {
    switch (t) {
        case TIMER1: return &TCCR1C;
        case TIMER3: return &TCCR3C;
        case TIMER4: return &TCCR4C;
        case TIMER5: return &TCCR5C;
        default:    return 0;
    }
}
static inline volatile uint8_t *timsk_reg(Timer_t t) {
    switch (t) {
        case TIMER0: return &TIMSK0;
        case TIMER1: return &TIMSK1;
        case TIMER2: return &TIMSK2;
        case TIMER3: return &TIMSK3;
        case TIMER4: return &TIMSK4;
        case TIMER5: return &TIMSK5;
    }
    return 0;
}
static inline volatile uint8_t *tifr_reg(Timer_t t) {
    switch (t) {
        case TIMER0: return &TIFR0;
        case TIMER1: return &TIFR1;
        case TIMER2: return &TIFR2;
        case TIMER3: return &TIFR3;
        case TIMER4: return &TIFR4;
        case TIMER5: return &TIFR5;
    }
    return 0;
}

static inline uint8_t width_of(Timer_t t)
{
    return (t == TIMER0 || t == TIMER2) ? 8 : 16;
}

/* ---- Per-timer COM / FOC bit number helpers ---- */
static inline uint8_t coma1_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return COM0A1;
        case TIMER1: return COM1A1;
        case TIMER2: return COM2A1;
        case TIMER3: return COM3A1;
        case TIMER4: return COM4A1;
        case TIMER5: return COM5A1;
    }
    return 0;
}
static inline uint8_t coma0_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return COM0A0;
        case TIMER1: return COM1A0;
        case TIMER2: return COM2A0;
        case TIMER3: return COM3A0;
        case TIMER4: return COM4A0;
        case TIMER5: return COM5A0;
    }
    return 0;
}
static inline uint8_t comb1_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return COM0B1;
        case TIMER1: return COM1B1;
        case TIMER2: return COM2B1;
        case TIMER3: return COM3B1;
        case TIMER4: return COM4B1;
        case TIMER5: return COM5B1;
    }
    return 0;
}
static inline uint8_t comb0_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return COM0B0;
        case TIMER1: return COM1B0;
        case TIMER2: return COM2B0;
        case TIMER3: return COM3B0;
        case TIMER4: return COM4B0;
        case TIMER5: return COM5B0;
    }
    return 0;
}
static inline uint8_t focA_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return FOC0A;
        case TIMER1: return FOC1A;
        case TIMER2: return FOC2A;
        case TIMER3: return FOC3A;
        case TIMER4: return FOC4A;
        case TIMER5: return FOC5A;
    }
    return 0;
}
static inline uint8_t focB_bit(Timer_t t) {
    switch (t) {
        case TIMER0: return FOC0B;
        case TIMER1: return FOC1B;
        case TIMER2: return FOC2B;
        case TIMER3: return FOC3B;
        case TIMER4: return FOC4B;
        case TIMER5: return FOC5B;
    }
    return 0;
}

/* ---- TIMSK / TIFR bit positions (same numbering for all timers: 0..7) ----
 * TOIEn / OCIEnA..C / TOVn / OCFnA..C share the same numeric bit position
 * across all timers (TOIE0 == TOIE1 == ... == 0, OCIE0A == OCIE1A == ... == 1, etc.)
 */
#define BIT_TOIE   0
#define BIT_OCIEA  1
#define BIT_OCIEB  2
#define BIT_OCIEC  3

#define BIT_TOV    0
#define BIT_OCFA   1
#define BIT_OCFB   2
#define BIT_OCFC   3

/* ---- Public API ---- */

void Timer_Init(const TimerConfig_t *cfg)
{
    if (!cfg) return;
    Timer_t t = cfg->timer;
    if ((uint8_t)t > 5) return;

    volatile uint8_t *tccra = tccra_reg(t);
    volatile uint8_t *tccrb = tccrb_reg(t);
    volatile uint8_t *timsk = timsk_reg(t);

    if (!tccra || !tccrb || !timsk) return;

    /* Stop the timer while configuring */
    *tccrb &= (uint8_t)~((1 << CS02) | (1 << CS01) | (1 << CS00));

    /* Apply WGM mode bits */
    apply_wgm_bits(t, cfg->mode);

    /* Disable all interrupts for this timer */
    *timsk = 0;

    /* Reset counter and compare values */
    Timer_SetCounter(t, 0);
    Timer_SetCompareA(t, 0);
    Timer_SetCompareB(t, 0);
    if (width_of(t) == 16) Timer_SetCompareC(t, 0);

    /* Apply prescaler (starts the timer) */
    s_prescalers[(uint8_t)t] = (uint8_t)(cfg->prescaler & 0x07);
    *tccrb = (uint8_t)((*tccrb & ~((1 << CS02) | (1 << CS01) | (1 << CS00)))
                       | s_prescalers[(uint8_t)t]);
}

void Timer_Stop(Timer_t t)
{
    volatile uint8_t *tccrb = tccrb_reg(t);
    *tccrb &= (uint8_t)~((1 << CS02) | (1 << CS01) | (1 << CS00));
}

void Timer_Start(Timer_t t)
{
    volatile uint8_t *tccrb = tccrb_reg(t);
    if (!tccrb) return;

    uint8_t cs = s_prescalers[(uint8_t)t];
    if (cs == 0) cs = TIMER_PRESCALER_1;
    *tccrb = (uint8_t)((*tccrb & ~((1 << CS02) | (1 << CS01) | (1 << CS00))) | cs);
}

void Timer_SetCounter(Timer_t t, uint16_t value)
{
    volatile uint8_t *lo = tcnt_lo(t);
    volatile uint8_t *hi = tcnt_hi(t);
    if (hi) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            *hi = (uint8_t)(value >> 8);
            *lo = (uint8_t)(value & 0xFF);
        }
    } else {
        *lo = (uint8_t)(value & 0xFF);
    }
}

uint16_t Timer_GetCounter(Timer_t t)
{
    volatile uint8_t *lo = tcnt_lo(t);
    volatile uint8_t *hi = tcnt_hi(t);
    if (hi) {
        uint8_t h, l;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            h = *hi;
            l = *lo;
            if (*hi != h) {
                h = *hi;
                l = *lo;
            }
        }
        return ((uint16_t)h << 8) | l;
    } else {
        return *lo;
    }
}

void Timer_SetCompareA(Timer_t t, uint16_t value)
{
    volatile uint8_t *lo = ocra_lo(t);
    volatile uint8_t *hi = ocra_hi(t);
    if (hi) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            *hi = (uint8_t)(value >> 8);
            *lo = (uint8_t)(value & 0xFF);
        }
    } else {
        *lo = (uint8_t)(value & 0xFF);
    }
}

void Timer_SetCompareB(Timer_t t, uint16_t value)
{
    volatile uint8_t *lo = ocrb_lo(t);
    volatile uint8_t *hi = ocrb_hi(t);
    if (hi) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            *hi = (uint8_t)(value >> 8);
            *lo = (uint8_t)(value & 0xFF);
        }
    } else {
        *lo = (uint8_t)(value & 0xFF);
    }
}

void Timer_SetCompareC(Timer_t t, uint16_t value)
{
    volatile uint8_t *lo = ocrc_lo(t);
    volatile uint8_t *hi = ocrc_hi(t);
    if (!lo) return;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *hi = (uint8_t)(value >> 8);
        *lo = (uint8_t)(value & 0xFF);
    }
}

void Timer_SetICR(Timer_t t, uint16_t value)
{
    volatile uint8_t *lo = icr_lo(t);
    volatile uint8_t *hi = icr_hi(t);
    if (!lo) return;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        *hi = (uint8_t)(value >> 8);
        *lo = (uint8_t)(value & 0xFF);
    }
}

void Timer_SetOutputCompareA(Timer_t t, TimerOCMode_t mode)
{
    volatile uint8_t *tccra = tccra_reg(t);
    uint8_t coma1 = coma1_bit(t);
    uint8_t coma0 = coma0_bit(t);
    *tccra = (uint8_t)((*tccra & ~((1 << coma1) | (1 << coma0)))
                       | (((uint8_t)mode & 0x03) << coma0));
}

void Timer_SetOutputCompareB(Timer_t t, TimerOCMode_t mode)
{
    volatile uint8_t *tccra = tccra_reg(t);
    uint8_t comb1 = comb1_bit(t);
    uint8_t comb0 = comb0_bit(t);
    *tccra = (uint8_t)((*tccra & ~((1 << comb1) | (1 << comb0)))
                       | (((uint8_t)mode & 0x03) << comb0));
}

void Timer_ForceCompareA(Timer_t t)
{
    uint8_t bit = focA_bit(t);
    if (width_of(t) == 16) {
        volatile uint8_t *tccrc = tccrc_reg(t);
        *tccrc |= (1 << bit);
    } else {
        volatile uint8_t *tccra = tccra_reg(t);
        *tccra |= (1 << bit);
    }
}

void Timer_ForceCompareB(Timer_t t)
{
    uint8_t bit = focB_bit(t);
    if (width_of(t) == 16) {
        volatile uint8_t *tccrc = tccrc_reg(t);
        *tccrc |= (1 << bit);
    } else {
        volatile uint8_t *tccra = tccra_reg(t);
        *tccra |= (1 << bit);
    }
}

/* ---- Interrupt handling ---- */

static inline uint8_t int_bit(TimerIntSrc_t src)
{
    switch (src) {
        case TIMER_INT_OVERFLOW: return BIT_TOIE;
        case TIMER_INT_COMPA:    return BIT_OCIEA;
        case TIMER_INT_COMPB:    return BIT_OCIEB;
        case TIMER_INT_COMPC:    return BIT_OCIEC;
    }
    return 0;
}

static inline uint8_t int_flag_bit(TimerIntSrc_t src)
{
    switch (src) {
        case TIMER_INT_OVERFLOW: return BIT_TOV;
        case TIMER_INT_COMPA:    return BIT_OCFA;
        case TIMER_INT_COMPB:    return BIT_OCFB;
        case TIMER_INT_COMPC:    return BIT_OCFC;
    }
    return 0;
}

void Timer_EnableInterrupt(Timer_t t, TimerIntSrc_t src)
{
    volatile uint8_t *timsk = timsk_reg(t);
    *timsk |= (uint8_t)(1 << int_bit(src));
}

void Timer_DisableInterrupt(Timer_t t, TimerIntSrc_t src)
{
    volatile uint8_t *timsk = timsk_reg(t);
    *timsk &= (uint8_t)~(1 << int_bit(src));
}

void Timer_RegisterCallback(Timer_t t, TimerIntSrc_t src, TimerCallback_t cb)
{
    s_callbacks[(uint8_t)t][(uint8_t)src] = cb;
}

uint8_t Timer_GetFlag(Timer_t t, TimerIntSrc_t src)
{
    volatile uint8_t *tifr = tifr_reg(t);
    return (*tifr & (1 << int_flag_bit(src))) ? 1u : 0u;
}

void Timer_ClearFlag(Timer_t t, TimerIntSrc_t src)
{
    volatile uint8_t *tifr = tifr_reg(t);
    *tifr = (uint8_t)(1 << int_flag_bit(src));
}

void Timer_GlobalIrqEnable(void)  { sei(); }
void Timer_GlobalIrqDisable(void) { cli(); }

static inline void dispatch(Timer_t t, TimerIntSrc_t src)
{
    TimerCallback_t cb = s_callbacks[(uint8_t)t][(uint8_t)src];
    if (cb) cb();
}

/* ---- ISRs ---- */
ISR(TIMER0_OVF_vect)  { dispatch(TIMER0, TIMER_INT_OVERFLOW); }
ISR(TIMER0_COMPA_vect){ dispatch(TIMER0, TIMER_INT_COMPA); }
ISR(TIMER0_COMPB_vect){ dispatch(TIMER0, TIMER_INT_COMPB); }

ISR(TIMER1_OVF_vect)  { dispatch(TIMER1, TIMER_INT_OVERFLOW); }
ISR(TIMER1_COMPA_vect){ dispatch(TIMER1, TIMER_INT_COMPA); }
ISR(TIMER1_COMPB_vect){ dispatch(TIMER1, TIMER_INT_COMPB); }
ISR(TIMER1_COMPC_vect){ dispatch(TIMER1, TIMER_INT_COMPC); }

ISR(TIMER2_OVF_vect)  { dispatch(TIMER2, TIMER_INT_OVERFLOW); }
ISR(TIMER2_COMPA_vect){ dispatch(TIMER2, TIMER_INT_COMPA); }
ISR(TIMER2_COMPB_vect){ dispatch(TIMER2, TIMER_INT_COMPB); }

ISR(TIMER3_OVF_vect)  { dispatch(TIMER3, TIMER_INT_OVERFLOW); }
ISR(TIMER3_COMPA_vect){ dispatch(TIMER3, TIMER_INT_COMPA); }
ISR(TIMER3_COMPB_vect){ dispatch(TIMER3, TIMER_INT_COMPB); }
ISR(TIMER3_COMPC_vect){ dispatch(TIMER3, TIMER_INT_COMPC); }

ISR(TIMER4_OVF_vect)  { dispatch(TIMER4, TIMER_INT_OVERFLOW); }
ISR(TIMER4_COMPA_vect){ dispatch(TIMER4, TIMER_INT_COMPA); }
ISR(TIMER4_COMPB_vect){ dispatch(TIMER4, TIMER_INT_COMPB); }
ISR(TIMER4_COMPC_vect){ dispatch(TIMER4, TIMER_INT_COMPC); }

ISR(TIMER5_OVF_vect)  { dispatch(TIMER5, TIMER_INT_OVERFLOW); }
ISR(TIMER5_COMPA_vect){ dispatch(TIMER5, TIMER_INT_COMPA); }
ISR(TIMER5_COMPB_vect){ dispatch(TIMER5, TIMER_INT_COMPB); }
ISR(TIMER5_COMPC_vect){ dispatch(TIMER5, TIMER_INT_COMPC); }

/* ---- Period computation ---- */
static const uint16_t prescalers[] = {0, 1, 8, 32, 64, 128, 256, 1024};
static const uint8_t  num_prescalers = 8;

bool Timer_ComputePeriod16(TimerMode_t mode, uint32_t period_us,
                           TimerPrescaler_t *out_prescaler,
                           uint16_t *out_top,
                           uint32_t *actual_period_us)
{
    (void)mode;
    uint32_t top_min = 1, top_max = 0xFFFF;

    uint32_t best_err = 0xFFFFFFFFu;
    TimerPrescaler_t best_ps = TIMER_PRESCALER_1;
    uint16_t best_top = 0;
    bool found = false;

    for (uint8_t i = 1; i < num_prescalers; i++) {
        uint32_t ps = prescalers[i];
        uint64_t ticks = ((uint64_t)period_us * (F_CPU / 1000000UL)) / ps;
        if (ticks < top_min || ticks > top_max) continue;

        uint16_t top = (uint16_t)(ticks - 1);
        uint32_t actual_ticks = (uint32_t)top + 1;
        uint64_t actual_us = (actual_ticks * ps * 1000000UL) / F_CPU;
        uint32_t err = (actual_us > period_us) ?
                       (uint32_t)(actual_us - period_us) :
                       (uint32_t)(period_us - actual_us);
        if (err < best_err) {
            best_err = err;
            best_ps = (TimerPrescaler_t)i;
            best_top = top;
            found = true;
            if (err == 0) break;
        }
    }

    if (!found) return false;
    if (out_prescaler)    *out_prescaler = best_ps;
    if (out_top)          *out_top = best_top;
    if (actual_period_us) {
        uint32_t actual_ticks = (uint32_t)best_top + 1;
        *actual_period_us = (uint32_t)((uint64_t)actual_ticks * prescalers[best_ps] * 1000000UL / F_CPU);
    }
    return true;
}

bool Timer_ComputePeriod8(TimerMode_t mode, uint32_t period_us,
                          TimerPrescaler_t *out_prescaler,
                          uint16_t *out_top,
                          uint32_t *actual_period_us)
{
    (void)mode;
    uint32_t top_min = 1, top_max = 0xFF;

    uint32_t best_err = 0xFFFFFFFFu;
    TimerPrescaler_t best_ps = TIMER_PRESCALER_1;
    uint16_t best_top = 0;
    bool found = false;

    for (uint8_t i = 1; i < num_prescalers; i++) {
        uint32_t ps = prescalers[i];
        uint64_t ticks = ((uint64_t)period_us * (F_CPU / 1000000UL)) / ps;
        if (ticks < top_min || ticks > top_max) continue;

        uint16_t top = (uint16_t)(ticks - 1);
        uint32_t actual_ticks = (uint32_t)top + 1;
        uint64_t actual_us = (actual_ticks * ps * 1000000UL) / F_CPU;
        uint32_t err = (actual_us > period_us) ?
                       (uint32_t)(actual_us - period_us) :
                       (uint32_t)(period_us - actual_us);
        if (err < best_err) {
            best_err = err;
            best_ps = (TimerPrescaler_t)i;
            best_top = top;
            found = true;
            if (err == 0) break;
        }
    }

    if (!found) return false;
    if (out_prescaler)    *out_prescaler = best_ps;
    if (out_top)          *out_top = best_top;
    if (actual_period_us) {
        uint32_t actual_ticks = (uint32_t)best_top + 1;
        *actual_period_us = (uint32_t)((uint64_t)actual_ticks * prescalers[best_ps] * 1000000UL / F_CPU);
    }
    return true;
}