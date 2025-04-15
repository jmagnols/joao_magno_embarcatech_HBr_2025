#include <stdio.h>               // I/O
#include "pico/stdlib.h" 
#include "pico/time.h"           // tempo
#include "hardware/i2c.h"        // Comunicação I2C
#include "hardware/gpio.h"
#include "inc/ssd1306.h"         // Controle do OLED SSD1306
#include <string.h>

// Pinos botões e OLED
#define I2C_PORT i2c1            // porta I2C1
#define SDA_PIN 14               // SDA
#define SCL_PIN 15               // SCL
#define DEBOUNCE_TIME_MS 300 
#define BUTTON_A 5               // botão A reinicia a contagem
#define BUTTON_B 6               // btoão B conta clique

// vars globais
volatile int counter = 9;         // valor inicial do contador
volatile int button_b_clicks = 0; // cont de cliques do botão B
volatile bool active = false;     // contador ativo
volatile bool update_display = false; // att do display necessária

// renderização para o OLED
uint8_t oled_buffer[ssd1306_buffer_length];
struct render_area oled_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// debounce
absolute_time_t last_button_a_time = { 0 };
absolute_time_t last_button_b_time = { 0 };

// att o OLED com contador e clique
void att_oled() {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    char msg[40];
    sprintf(msg, "contador: %d", counter);
    ssd1306_draw_string(oled_buffer, 5, 10, msg);
    sprintf(msg, "clicks B: %d", button_b_clicks);
    ssd1306_draw_string(oled_buffer, 5, 30, msg);
    sprintf(msg, "reiniciar A");
    ssd1306_draw_string(oled_buffer, 5, 50, msg);
    calculate_render_area_buffer_length(&oled_area);
    render_on_display(oled_buffer, &oled_area);
}

// callback de interrupção dos botões
void gpio_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) {
        if (absolute_time_diff_us(last_button_a_time, now) > DEBOUNCE_TIME_MS * 1000) {
            counter = 9;
            button_b_clicks = 0;
            active = true;
            update_display = true;
            last_button_a_time = now;
        }
    }
    if (gpio == BUTTON_B && (events & GPIO_IRQ_EDGE_FALL)) {
        if (active && (absolute_time_diff_us(last_button_b_time, now) > DEBOUNCE_TIME_MS * 1000)) {
            button_b_clicks++;
            update_display = true;
            last_button_b_time = now;
        }
    }
}

// callback timer (1 segundo)
bool timer_callback(repeating_timer_t* rt) {
    if (active) {
        if (counter > 0)
            counter--;
        else
            active = false;
        update_display = true;
    }
    return true;
}

int main() {
    stdio_init_all();

    // init I2C para o OLED
    i2c_init(I2C_PORT, ssd1306_i2c_clock * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // configura botões como entrada com pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);  // botao a
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B); // botao b

    // configura interrupções dos botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    // init do OLED
    ssd1306_init();
    att_oled();

    // timer 1 segundo pra update do display
    repeating_timer_t timer;
    add_repeating_timer_ms(1000, timer_callback, NULL, &timer);

    // loop principal: atualiza o display se necessário
    while (true) {
        if (update_display) {
            att_oled();
            update_display = false;
        }
        sleep_ms(50);
    }
    return 0;
}

