#include <math.h>
#include <stdint.h>
#include "temperature.h"
#include "adc_setup_dma.h"

#define USE_PT100 0 // Defina como 1 para PT100, 0 para LM35

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

#if USE_PT100
    // Cálculo baseado na equação IEC 751 para PT100
    float resistance = (voltage * R_FIXED) / (3.3f - voltage);
    float temperature = (-3.9083e-3 + sqrt((3.9083e-3 * 3.9083e-3) - (4 * -5.775e-7 * (1 - (resistance / 100.0))))) / (2 * -5.775e-7);
#else
    // LM35: A saída é diretamente proporcional à temperatura (10mV/°C)
    float temperature = (voltage * 100.0f); // Converte tensão para temperatura (°C)
#endif

    return temperature;
}