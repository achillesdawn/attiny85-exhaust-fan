#include "adc.h"
#include <Arduino.h>

volatile uint16_t adc_value;

// ISR(ADC_vect) { adc_value = ADCL | (ADCH << 8); }

void Adc::initADC() {
    /* this function initialises the ADC

          ADC Prescaler Notes:
          --------------------

    ADC Prescaler needs to be set so that the ADC input frequency is
    between 50 - 200kHz.

    For more information, see table 17.5 "ADC Prescaler Selections" in
    chapter 17.13.2 "ADCSRA – ADC Control and Status Register A"
    (pages 140 and 141 on the complete ATtiny25/45/85 datasheet, Rev.
    2586M–AVR–07/10)

    Valid prescaler values for various clock speeds

    Clock   Available prescaler values
    ---------------------------------------
    1 MHz     8 (125kHz), 16 (62.5kHz)
    4 MHz    32 (125kHz), 64 (62.5kHz)
    8 MHz    64 (125kHz), 128 (62.5kHz)
    16 MHz  128 (125kHz)

    Below example set prescaler to 128 for mcu running at 8MHz
    (check the datasheet for the proper bit values to set the  prescaler)
    */

    // 8-bit resolution
    // set ADLAR to 1 to enable the Left-shift result (only bits ADC9..ADC2
    // are available) then, only reading ADCH is sufficient for 8-bit
    // results (256 values)

    ADMUX = (1 << ADLAR) | // left shift result
            (0 << REFS1) | // Sets ref. voltage to VCC, bit 1
            (0 << REFS0) | // Sets ref. voltage to VCC, bit 0
            (0 << MUX3) |  // use ADC2 for input (PB4), MUX bit 3
            (0 << MUX2) |  // use ADC2 for input (PB4), MUX bit 2
            (1 << MUX1) |  // use ADC2 for input (PB4), MUX bit 1
            (0 << MUX0);   // use ADC2 for input (PB4), MUX bit 0

    ADCSRA = (1 << ADEN) |  // Enable ADC
             (1 << ADPS2) | // set prescaler to 64, bit 2
             (1 << ADPS1) | // set prescaler to 64, bit 1
             (0 << ADPS0);  // set prescaler to 64, bit 0
};

void Adc::voltage_reference_vcc() {
    ADMUX |= (0 << REFS2) | (0 << REFS1) | (0 << REFS0);
};

void Adc::voltage_reference_PB0() {
    ADMUX |= (0 << REFS2) | (0 << REFS1) | (1 << REFS0);
};

void Adc::voltage_reference_internal_1v1() {
    ADMUX |= (0 << REFS2) | (1 << REFS1) | (0 << REFS0);
};

void Adc::voltage_reference_2v56(bool external_bypass) {
    if (external_bypass) {

        // Internal 2.56V Voltage Reference without external bypass
        // capacitor, disconnected from PB0 (AREF).
        ADMUX |= (1 << REFS2) | (1 << REFS1) | (0 << REFS0);

    } else {
        // Internal 2.56V Voltage Reference with external bypass capacitor
        // at PB0 (AREF) pin.
        ADMUX |= (1 << REFS2) | (1 << REFS1) | (1 << REFS0);
    }
}

void Adc::set_result_shifted(bool left) {
    if (left) {
        ADMUX |= (1 << ADLAR);

    } else {
        ADMUX |= (0 << ADLAR);
    }
}

void Adc::enable_adc() {
    ADCSRA |= (1 << ADEN); // Enable ADC
};

void Adc::clock_prescale() {
    ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void Adc::start() { ADCSRA |= (1 << ADSC); }

void Adc::wait_for_conversion() {
    while (ADCSRA & (1 << ADSC) == 1) {
    }
}

void Adc::set_adc_single_ended_input(uint8_t pin_number) {
    switch (pin_number) {

    case 2:
        ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0);
        break;

    case 3:
        ADMUX |= (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0);
        break;

    case 4:
        ADMUX |= (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0);
        break;

    case 5:
        ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
        break;

    default:
        // internal temperature sensor
        ADMUX |= (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
        break;
    }
}

void Adc::read_adc() { adc_value = ADCL | (ADCH << 8); }
