#ifndef TEMPERATURE_H  // Verifica se o macro TEMPERATURE_H não está definido
#define TEMPERATURE_H  // Define o macro TEMPERATURE_H para evitar a inclusão múltipla do arquivo de cabeçalho

// Declaração da função 'read_temperature', sua implementação encontra-se em temperature.c
// Esta função será usada para ler a temperatura do sensor, retornando um valor float.
float get_temperature_from_dma(void);  // A função read_temperature retorna um valor float representando a temperatura lida do sensor

#endif  // Fim da diretiva de inclusão condicional
