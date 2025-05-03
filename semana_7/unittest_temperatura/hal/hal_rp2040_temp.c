#include "hal_rp2040_temp.h"
#include "rp2040_temp_sensor.h"
#include <stdio.h>

float adc_to_celsius(uint16_t adcValue) {
    const float conversionFactor = 3.3f / 4095; // adc to voltage conversion (12 bits)
    float voltage = adcValue * conversionFactor; // converts adc value to voltage
    printf("hal voltage: %.3f V\n", voltage); // debug voltage output
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f; // voltage to celsius conversion
    printf("hal temperature: %.2f C\n", temperature); // debug temperature output
    return temperature;
}

float hal_temperature_read_rp2040() {
    uint16_t adcValue = rp2040_temp_sensor_read(); // read temperature sensor
    printf("hal adc value: %d\n", adcValue); // debug adc value output
    return adc_to_celsius(adcValue); // return converted celsius value
}