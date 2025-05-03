#include "hal_led.h"
#include "led_dentro.h"

static bool led_state = false;

void hal_led_toggle(void) {
    led_state = !led_state;
    led_dentro_set(led_state); // toggle led state and update hardware
}