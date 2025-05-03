#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_rp2040_temp.h"

int main() {
    stdio_init_all();
    rp2040_temp_sensor_init();

    float temperature;

    while (true) {
        sleep_ms(1000);
        temperature = hal_temperature_read_rp2040(); // read temperature value
        printf("temperature: %.2f C\n", temperature); // print temperature to console
    }

    return 0;
}