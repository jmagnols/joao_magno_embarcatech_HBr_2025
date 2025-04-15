#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"    // ADC
#include "hardware/gpio.h"
#include "hardware/i2c.h"    // I2C
#include "inc/ssd1306.h"     // OLED SSD1306

#define JOY_SW  22        // Botão joystick
#define VRY_PIN 27        // ADC joystick Y
#define VRX_PIN 26        // ADC joystick X

#define ADC_CH_X 0        // ADC X
#define ADC_CH_Y 1        // ADC Y

// Config pinos e I2C
#define I2C_PORT i2c1        // porta I2C1
#define I2C_SPEED 100000     // 100 kHz
#define SDA_PIN 14        // SDA to I2C
#define SCL_PIN 15        // SCL to I2C


// Buffer e área de renderização para o OLED
uint8_t oled_buffer[ssd1306_buffer_length];
struct render_area oled_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// Inicializa I2C e OLED
bool setup_display() {
    i2c_init(I2C_PORT, I2C_SPEED);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    sleep_ms(200);

    ssd1306_init();
    memset(oled_buffer, 0, sizeof(oled_buffer));
    ssd1306_draw_string(oled_buffer, 0, 0, "Display OK!");
    calculate_render_area_buffer_length(&oled_area);
    render_on_display(oled_buffer, &oled_area);
    sleep_ms(1000);
    return true;
}

// config do joystick
void setup_joystick() {
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
    gpio_init(JOY_SW);
    gpio_set_dir(JOY_SW, GPIO_IN);
    gpio_pull_up(JOY_SW);
}

// le os valores do joystick
void joystick_read(uint16_t *eixo_x, uint16_t *eixo_y) {
    adc_select_input(ADC_CH_X);
    sleep_us(5);
    *eixo_x = adc_read();
    adc_select_input(ADC_CH_Y);
    sleep_us(5);
    *eixo_y = adc_read();
}

// display dos valores no LED
void oled_valueshow(uint16_t eixo_x, uint16_t eixo_y, uint8_t botao) {
    memset(oled_buffer, 0, sizeof(oled_buffer));

    char linha1[22], linha2[22], linha3[22], linha4[22];
    snprintf(linha1, sizeof(linha1), "Joystick test:");
    snprintf(linha2, sizeof(linha2), "X: %d", eixo_x);
    snprintf(linha3, sizeof(linha3), "Y: %d", eixo_y);
    snprintf(linha4, sizeof(linha4), "Button: %s", botao ? "on 1" : "off 0");

    ssd1306_draw_string(oled_buffer, 0, 0, linha1);
    ssd1306_draw_string(oled_buffer, 0, 20, linha2);
    ssd1306_draw_string(oled_buffer, 0, 35, linha3);
    ssd1306_draw_string(oled_buffer, 0, 50, linha4);
    calculate_render_area_buffer_length(&oled_area);
    render_on_display(oled_buffer, &oled_area);
}

// Configs gerais
void setup() {
    stdio_init_all();
    setup_joystick();
    if (!setup_display()) {
        printf("houve um erro no display\n");
    }
}

int main() {
    uint16_t x = 0, y = 0;
    uint8_t botao = 0;
    setup();
    printf("começando leitura do joystick\n");

    while (1) {  // loop de funcionamento
        joystick_read(&x, &y);
        botao = !gpio_get(JOY_SW);
        printf("X: %d, Y: %d, botao: %s\n", x, y, botao ? "ON 1" : "OFF 0");

        oled_valueshow(x, y, botao);
        sleep_ms(500);
    }
}

