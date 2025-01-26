#include "pwm.h"
#include <avr/pgmspace.h>

void set_pwm_mode(uint8_t mode) {

    // datasheet page 79
    // TCCR0A – Timer/Counter Control Register A

    switch (mode) {
    case 0:
        // mode: normal
        TCCR0B |= (0 << WGM02);
        TCCR0A |= (0 << WGM01) | (0 << WGM00);
        break;

    case 1:
        // mode: phase correct PWM with top at 255 (0xFF) (8 bit register max)
        TCCR0B |= (0 << WGM02);
        TCCR0A |= (0 << WGM01) | (1 << WGM00);
        break;

    case 2:
        // mode: clear timer on compare
        TCCR0B |= (0 << WGM02);
        TCCR0A |= (1 << WGM01) | (0 << WGM00);
        break;

    case 3:
        // mode: fast PWM mode with top at 255
        TCCR0B |= (0 << WGM02);
        TCCR0A |= (1 << WGM01) | (1 << WGM00);
        break;

    case 4:
        // RESERVED (not enabled)
        break;

    case 5:
        // mode: PWM, phase correct with top at OCRA
        TCCR0B |= (1 << WGM02);
        TCCR0A |= (0 << WGM01) | (1 << WGM00);
        break;

    case 6:
        // RESERVED (not enabled)
        break;

    case 7:
        // mode: fast PWM mode with top at OCRA
        TCCR0B |= (1 << WGM02);
        TCCR0A |= (1 << WGM01) | (1 << WGM00);
        break;
    default:
        break;
    }
}

void set_pwm_timer_prescaling(uint8_t mode) {

    // section 11.9.3 of datasheet page 79
    // Timer/Counter Control Register B

    GTCCR |= (1 << TSM);

    switch (mode) {
    case 0:
        // no clock source / timer stopped
        TCCR0B |= (0 << CS02) | (0 << CS01) | (0 << CS00);
        break;

    case 1:
        // no prescaling
        TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00);
        break;

    case 2:
        // 8 prescale
        TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);
        break;

    case 3:
        // 64 prescale
        TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
        break;

    case 4:
        // 256 prescale
        TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
        break;

    case 5:
        // 1024 prescale
        TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
        break;

    case 6:

        // external clock source on T0 pin. Clock on falling edge.
        TCCR0B |= (1 << CS02) | (1 << CS01) | (0 << CS00);
        break;

    case 7:
        // External clock source on T0 pin. Clock on rising edge.
        TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00);
        break;
    default:
        break;
    }

    GTCCR &= ~(1 << TSM);
}

typedef enum {
    T1_PRESCALE_STOPPED,
    T1_PRESCALE_NONE,
    T1_PRESCALE_DIV_2,
    T1_PRESCALE_DIV_4,
    T1_PRESCALE_DIV_8,
    T1_PRESCALE_DIV_16,
    T1_PRESCALE_DIV_32,
    T1_PRESCALE_DIV_64,
    T1_PRESCALE_DIV_128,
    T1_PRESCALE_DIV_256,
    T1_PRESCALE_DIV_512,
    T1_PRESCALE_DIV_1024,
    T1_PRESCALE_DIV_2048,
    T1_PRESCALE_DIV_4096,
    T1_PRESCALE_DIV_8192,
    T1_PRESCALE_DIV_16384
} PrescalerValue;

void set_timer1_prescaling(PrescalerValue prescaler) {

    switch (prescaler) {
        {
        case T1_PRESCALE_STOPPED:
            TCCR1 |= (0 << CS13) | (0 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_NONE:
            TCCR1 |= (0 << CS13) | (0 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_2:
            TCCR1 |= (0 << CS13) | (0 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_4:
            TCCR1 |= (0 << CS13) | (0 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_8:
            TCCR1 |= (0 << CS13) | (1 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_16:
            TCCR1 |= (0 << CS13) | (1 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_32:
            TCCR1 |= (0 << CS13) | (1 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_64:
            TCCR1 |= (0 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_128:
            TCCR1 |= (1 << CS13) | (0 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_256:
            TCCR1 |= (1 << CS13) | (0 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_512:
            TCCR1 |= (1 << CS13) | (0 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_1024:
            TCCR1 |= (1 << CS13) | (0 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_2048:
            TCCR1 |= (1 << CS13) | (1 << CS12) | (0 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_4096:
            TCCR1 |= (1 << CS13) | (1 << CS12) | (0 << CS11) | (1 << CS10);
            break;
        case T1_PRESCALE_DIV_8192:
            TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (0 << CS10);
            break;
        case T1_PRESCALE_DIV_16384:
            TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10);
            break;
        default:
            break;
        }
    }
}

inline void set_compare_output_mode_pwm_phase_correct() {
    // non inverted
    TCCR0A |= (1 << COM0A1) | (0 << COM0A0);
    // TCCR0A |= (1 << COM0B1) | (0 << COM0B0);

    // inverted output
    // TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
}

inline void set_duty_output_compare_registry_a() {
    // 50% duty
    OCR0A = 128;
}

void setup_pwm_timer_0() {
    // Port B Data Direction Register
    // DDRB sets direction of pins

    // set direction of pin 0 as output
    DDRB |= (1 << DDB0);

    set_pwm_mode(1);
    set_pwm_timer_prescaling(1);
    set_compare_output_mode_pwm_phase_correct();
    set_duty_output_compare_registry_a();
}

void setup_pwm_timer_1() {
    // set direction of pin 0 as output
    DDRB |= (1 << DDB1);

    // PWM1A: Pulse Width Modulator A Enable
    TCCR1 |= (1 << PWM1A);

    // COM1A[1:0]: Comparator A Output Mode,
    // OC1x cleared on compare match. Set when TCNT1 = $00.
    TCCR1 |= (1 << COM1A1) | (0 << COM1A0);

    // timer one counts from 0 to OCR1C
    OCR1C = 255;

    set_timer1_prescaling(T1_PRESCALE_DIV_64);
}