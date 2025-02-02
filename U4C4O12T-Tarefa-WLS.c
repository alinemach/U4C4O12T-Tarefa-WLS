#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

// Definições de pinos
#define LED_RED 13
#define LED_WS2812 7
#define BUTTON_A 5
#define BUTTON_B 6

// Variáveis globais
volatile uint32_t last_time_a = 0;
volatile uint32_t last_time_b = 0;
volatile int numero_atual = 0; // Número a ser exibido na matriz

// Buffer da matriz WS2812
#define NUM_PIXELS 25
uint32_t led_buffer[NUM_PIXELS] = {0};
PIO pio = pio0;
int sm = 0;

// Funções auxiliares
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Função para exibir número na matriz
void exibir_numero(int num) {
    // Lógica para exibir números 0-9 na matriz (exemplo básico)
    for (int i = 0; i < NUM_PIXELS; i++) {
        led_buffer[i] = 0;
    }
    
    if (num % 2 == 0) {
        led_buffer[12] = urgb_u32(80, 0, 0); // Marca o centro como referência
    } else {
        led_buffer[12] = urgb_u32(0, 80, 0);
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(led_buffer[i]);
    }
}

// Interrupções dos botões com debounce
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    
    if (gpio == BUTTON_A && (current_time - last_time_a > 200000)) {
        last_time_a = current_time;
        numero_atual = (numero_atual + 1) % 10;
        exibir_numero(numero_atual);
    }
    
    if (gpio == BUTTON_B && (current_time - last_time_b > 200000)) {
        last_time_b = current_time;
        numero_atual = (numero_atual - 1 + 10) % 10;
        exibir_numero(numero_atual);
    }
}

int main() {
    stdio_init_all();
    
    // Inicialização dos LEDs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    // Inicialização dos botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    
    // Configuração das interrupções
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Inicialização da matriz WS2812
    int offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, LED_WS2812, 800000, false);

    // Loop principal (LED piscando)
    while (true) {
        gpio_put(LED_RED, 1);
        sleep_ms(100);
        gpio_put(LED_RED, 0);
        sleep_ms(100);
    }
}
