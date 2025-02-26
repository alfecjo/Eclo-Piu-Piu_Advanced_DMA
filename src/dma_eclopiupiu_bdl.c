#include <stdio.h>
#include <stdint.h>

#include "pico/stdio.h"

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

#include "i2c_setup.h"
#include "adc_setup_dma.h"
#include "oled_setup.h"
#include "temperature.h"

// Definição dos pinos de saída aos atuadores
#define FAN_PIN 8
#define LIGHT_PIN 9

// Limites de temperatura com histerese
#define TEMP_ON 38.0  // Liga a ventoinha acima de 38°C
#define TEMP_OFF 36.0 // Desliga a ventoinha abaixo de 36°C

// Estado dos dispositivos
bool fan_on = false;
bool light_on = false;

// Callback da interrupção do timer
bool temperatura_callback(struct repeating_timer *t)
{
    float temperatura = get_temperature_from_dma(); // Lê a temperatura

    // Lógica com histerese
    if (temperatura >= TEMP_ON)
    {
        if (!fan_on)
        { // Evita ligar se já estiver ligado
            gpio_put(FAN_PIN, 1);
            fan_on = true;
        }
        gpio_put(LIGHT_PIN, 0); // Garante que a luz está apagada
        light_on = false;
    }
    else if (temperatura <= TEMP_OFF)
    {
        if (fan_on)
        { // Evita desligar se já estiver desligado
            gpio_put(FAN_PIN, 0);
            fan_on = false;
        }
        gpio_put(LIGHT_PIN, 1);
        light_on = true;
    }

    // Atualiza o display OLED
    update_oled(temperatura);

    return true; // Mantém o timer rodando
}

void setup_initi_pin(void)
{
    // Configuração dos pinos da ventoinha e lâmpada
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);
    gpio_init(LIGHT_PIN);
    gpio_set_dir(LIGHT_PIN, GPIO_OUT);
}

int main()
{
    // Inicializa todos stdio vinculados ao binário
    stdio_init_all();

    // Configurações iniciais
    setup_i2c0();
    setup_adc_dma();
    setup_oled();
    setup_initi_pin();

    // Criando o timer que chamará a função a cada 15 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(5000, temperatura_callback, NULL, &timer);

    while (1)
    {
        sleep_ms(60000); // Mantém o programa rodando sem travar o processador
    }

    return 0;
}
