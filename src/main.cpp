#include <Arduino.h>
#include "adc.h"
#include "pwm.h"

void setup() {
    setup_pwm();
    DDRB |= (1 << DDB1);
}

void loop() {
    while (true) {
        PORTB |= (1 << PORTB1);
        delay(500);
        PORTB &= ~(1 << PORTB1);
        delay(500);
    }
}
