#include "pico/cyw43_arch.h"
#include "led_dentro.h"

void led_dentro_init(void) {
    if (cyw43_arch_init()) {
        while (true); // handle initialization failure
    }
}

void led_dentro_set(bool state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); // set led state (on/off)
}