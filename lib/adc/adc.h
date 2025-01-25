#pragma once

#include <Arduino.h>

class Adc {

  public:
    void initADC();

    void voltage_reference_vcc();

    void voltage_reference_PB0();

    void voltage_reference_internal_1v1();

    void voltage_reference_2v56(bool external_bypass);

    void set_result_shifted(bool left);

    void enable_adc();

    void set_adc_single_ended_input(uint8_t pin_number);

    void read_adc();

    void clock_prescale();

    void start();

    void wait_for_conversion();
};
