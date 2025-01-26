#include "adc.h"
#include "pwm.h"
#include <avr/pgmspace.h>

uint64_t current_time = 0;

void setup() {
    DDRB |= (1 << DDB0);
    setup_pwm_timer_1();
}

void sleep(uint64_t milliseconds) {
    current_time = millis();

    while (millis() - current_time <= milliseconds) {
        _NOPNOP();
    }
}

void loop() {

    for (uint8_t i = 0; i < 10; i++) {
        PORTB |= (1 << PB0);
        sleep(100);
        PORTB &= ~(1 << PB0);
        sleep(100);
    }

    for (uint8_t i = 0; i < 255; i++) {
        OCR1A = i;
        sleep(20);
    }

    for (uint8_t i = 255; i > 0; i--) {
        OCR1A = i;
        sleep(20);
    }
}
