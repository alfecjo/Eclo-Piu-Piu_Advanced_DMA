#ifndef OLED_SETUP_H  // Verifica se o macro OLED_SETUP_H não está definido
#define OLED_SETUP_H  // Define o macro OLED_SETUP_H para evitar a inclusão múltipla do arquivo de cabeçalho

// Declaração da função 'setup_oled'
// Esta função será usada para configurar o display OLED.
void setup_oled(void);  // Ambas funções setup_oled e update_oled, foram definidas em oled_setup.c

// Declaração da função 'update_oled'
// Esta função será usada para atualizar o conteúdo do display OLED com a temperatura.
void update_oled(float);  // A função update_oled recebe o valor da temperatura e atualiza o OLED

#endif  // Fim da diretiva de inclusão condicional
