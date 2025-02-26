#include "hardware/adc.h"
#include "hardware/dma.h"

#include "adc_setup_dma.h"

// Buffer de armazenamento das amostras do ADC
uint16_t adc_buffer[ADC_BUFFER_SIZE]; // <- Essa é a variável global usada no DMA
int dma_channel; // Canal do DMA

void setup_adc_dma()
{
    adc_init(); // Inicializa o ADC
    adc_gpio_init(28); // Configura GP28 como entrada do ADC

    adc_select_input(2); // Seleciona o canal do LM35 (GP28)
    adc_fifo_setup(
        true,  // Habilita o FIFO
        true,  // Ativa DMA
        1,     // Número mínimo de amostras antes de solicitar leitura
        false, // Sem erro de sobrecarga
        false  // Sem erro de push
    );

    adc_run(true); // Inicia o ADC

    // Configura o DMA
    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(dma_channel);
    
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16); // Transferência de 16 bits
    channel_config_set_read_increment(&cfg, false); // Não incrementar a fonte (ADC)
    channel_config_set_write_increment(&cfg, true); // Incrementar destino (buffer)
    channel_config_set_dreq(&cfg, DREQ_ADC); // Configura o trigger do DMA como ADC

    // Configura o canal DMA para transferir ADC_BUFFER_SIZE amostras
    dma_channel_configure(
        dma_channel, &cfg,
        adc_buffer,     // Endereço de destino (buffer)
        &adc_hw->fifo,  // Endereço da origem (ADC FIFO)
        ADC_BUFFER_SIZE,// Número de transferências
        true            // Inicia a transferência
    );
}
