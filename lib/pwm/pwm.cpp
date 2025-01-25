#include <Arduino.h>

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

void setup_pwm() {
    // Port B Data Direction Register
    // DDRB sets direction of pins

    // set direction of pin 0 as output
    DDRB |= (1 << DDB0);

    set_pwm_mode(1);
    set_pwm_timer_prescaling(5);
    set_compare_output_mode_pwm_phase_correct();
    set_duty_output_compare_registry_a();
}
