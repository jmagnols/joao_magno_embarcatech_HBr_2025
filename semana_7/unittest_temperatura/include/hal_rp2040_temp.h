#ifndef HAL_TEMPERATURE_H
#define HAL_TEMPERATURE_H

#include <stdint.h>
#include "rp2040_temp_sensor.h"

float adc_to_celsius(uint16_t adcValue);
float hal_temperature_read_rp2040();

#endif // HAL_TEMPERATURE_H