#include <stdio.h>

#include "ssd1306.h"
#include "oled_setup.h"

// Estrutura global do display
ssd1306_t disp; // Declara uma variável global para armazenar as configurações do display SSD1306

void setup_oled(void)
{
    // Configura a alimentação do display
    disp.external_vcc = false; // Define se o display usa alimentação externa (false indica que usa alimentação interna)

    // Inicializa o display SSD1306
    // Parâmetros: &disp (estrutura de configuração), 128 (largura do display), 64 (altura do display), 0x3C (endereço I2C do display), i2c1 (bus I2C utilizado)
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);

    // Limpa a tela do display
    ssd1306_clear(&disp); // Chama a função para apagar qualquer conteúdo da tela
}

// Função para atualizar a exibição no OLED (Temperatura ou Umidade)
void update_oled(float valor)
{
    char display_str[20]; // Declara um array de caracteres para armazenar a string com 20 caracteres de espaço

    // Se for temperatura, exibe com formato "Temp: X.X C"
    snprintf(display_str, sizeof(display_str), "Temp: %.1f C", valor);

    // Limpa a tela do display antes de atualizar com o novo valor
    ssd1306_clear(&disp);

    // Desenha a string (temperatura ou umidade) na posição X=10, Y=24 com o tamanho do texto 2
    ssd1306_draw_string(&disp, 10, 24, 2, display_str);

    // Atualiza o display com as informações desenhadas
    ssd1306_show(&disp); // Atualiza o conteúdo do display para mostrar a nova string
}