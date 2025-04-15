#include <stdio.h> 
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h" 
#include "hardware/i2c.h"     // I2C
#include "hardware/adc.h"     // ADC
#include "inc/ssd1306.h"      // OLED SSD1306

// configs OLED via I2C
#define SDA_PIN 14            // SDA
#define SCL_PIN 15            // SCL
#define I2C_PORT i2c1
#define I2C_SPEED 100000      // 100 kHz

// configs oled
uint8_t oled_buffer[ssd1306_buffer_length];  // buffer do OLED
struct render_area oled_area = {              // area de render do OLED
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// setup do sensor de temperatura interno da placa
void setup_sensor() {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

// init do I2C e OLED
bool setup_display() {
    i2c_init(I2C_PORT, I2C_SPEED);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    sleep_ms(200);

    ssd1306_init();
    memset(oled_buffer, 0, sizeof(oled_buffer));
    ssd1306_draw_string(oled_buffer, 0, 0, "Display ta ok!");
    calculate_render_area_buffer_length(&oled_area);
    render_on_display(oled_buffer, &oled_area);
    sleep_ms(1000);
    return true;
}

// lê temp interna (celsius)
float read_temperature() {
    uint16_t raw = adc_read();
    const float conv_factor = 3.3f / (1 << 12);
    float voltage = raw * conv_factor;
    return 27 - (voltage - 0.706) / 0.001721; // valores de offset e de calibração do sensor interno
}

// mostra temperatura no OLED
void oled_display_temperature(float temp) {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    char linha1[22], linha2[22];
    snprintf(linha1, sizeof(linha1), "internal temp:");
    snprintf(linha2, sizeof(linha2), "%.2f C", temp);
    ssd1306_draw_string(oled_buffer, 0, 0, linha1);
    ssd1306_draw_string(oled_buffer, 0, 30, linha2);
    calculate_render_area_buffer_length(&oled_area);
    render_on_display(oled_buffer, &oled_area);
}

// config geral
void setup() {
    stdio_init_all();
    setup_sensor();
    if (!setup_display()) {
        printf(" houve um erro ao inicializar o Display\n");
    }
}

// função main
int main() {
    setup();
    printf("Iniciando a leitura da temperatura...\n");
    while (1) {
        float temp = read_temperature();
        printf("temp: %.2f C\n", temp);
        oled_display_temperature(temp);
        sleep_ms(1000);
    }
}

