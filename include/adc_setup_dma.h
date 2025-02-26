#ifndef ADC_SETUP_DMA_H  // Verifica se o macro ADC_SETUP_H não está definido
#define ADC_SETUP_DMA_H  // Define o macro ADC_SETUP_H para evitar inclusão múltipla do arquivo de cabeçalho

#include <stdint.h>

#define ADC_BUFFER_SIZE 64  // Definição do tamanho do buffer

extern uint16_t adc_buffer[ADC_BUFFER_SIZE];  // Declaração externa do buffer

void setup_adc_dma(void);  // Inicialização do ADC e DMA

#endif