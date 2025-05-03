#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_rp2040_temp.h"
#include "Unity/unity.h"

void setUp() {}

void tearDown() {}

void test_temperature_read_rp2040() {
    float expectedTemp = 27.0f;
    uint16_t adcValue = 876; // simulated adc value for test
    printf("simulated adc value: %d\n", adcValue); // debug output
    float actualTemp = 0.0f;
    printf("initial temperature: %.2f C\n", actualTemp); // debug output
    actualTemp = adc_to_celsius(adcValue); // test conversion function
    printf("calculated temperature: %.2f C\n", actualTemp); // debug output

    TEST_ASSERT_FLOAT_WITHIN(0.1f, expectedTemp, actualTemp); // check value tolerance
}

void test_actual_temperature_read_rp2040(){
    float expectedTemp = 27.0f;
    float readTemp = hal_temperature_read_rp2040(); // read actual sensor
    printf("read temperature: %.2f C\n", readTemp); // debug output
    TEST_ASSERT_FLOAT_WITHIN(5.0f, expectedTemp, readTemp); // check sensor tolerance
}

int main(void) {
    stdio_init_all();
    rp2040_temp_sensor_init();
    
    while(true){
        UNITY_BEGIN();

        // execute test cases
        RUN_TEST(test_temperature_read_rp2040);
        RUN_TEST(test_actual_temperature_read_rp2040);
        printf("tests completed.\n");
        sleep_ms(3500);
    }

    return 0;
}