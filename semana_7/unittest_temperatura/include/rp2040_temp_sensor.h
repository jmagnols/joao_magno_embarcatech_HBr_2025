#ifndef RP2040_TEMP_SENSOR_H
#define RP2040_TEMP_SENSOR_H

#include <stdint.h>

void rp2040_temp_sensor_init();
uint16_t rp2040_temp_sensor_read();

#endif // RP2040_TEMP_SENSOR_H