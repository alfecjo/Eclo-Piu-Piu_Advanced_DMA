#include "temperature.h"
#include "adc_setup_dma.h"

float get_temperature_from_dma()
{
    uint32_t sum = 0;

    // Faz a média das amostras coletadas
    for (int i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        sum += adc_buffer[i];
    }

    float avg_raw = sum / (float)ADC_BUFFER_SIZE; // Média das amostras
    float voltage = avg_raw * (3.3f / (1 << 12)); // Conversão para tensão
    return voltage * 100.0f; // Conversão para temperatura (LM35)
}