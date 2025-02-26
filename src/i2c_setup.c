#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c_setup.h"

void setup_i2c0(void)
{
    i2c_init(i2c1, 400000);               // Inicializa I2C a 400kHz
    gpio_set_function(14, GPIO_FUNC_I2C); // Pino 14 para I2C
    gpio_set_function(15, GPIO_FUNC_I2C); // Pino 15 para I2C
    gpio_pull_up(14);                     // Habilita resistor pull-up no pino 14
    gpio_pull_up(15);                     // Habilita resistor pull-up no pino 15
}
