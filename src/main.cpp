#include "adc.h"
#include "pwm.h"
#include <Arduino.h>

void setup() {
    setup_pwm();
    DDRB |= (1 << DDB1);
}

void loop() {
    while (true) {
        for (uint8_t i = 0; i < 255; i++) {
            OCR0A = i;
            delay(20);
        }
    }
}
