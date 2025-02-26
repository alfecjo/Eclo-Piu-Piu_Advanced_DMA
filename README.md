### Observação importante:
Pode ser necessário algumas alterações no arquivo CMakeLists.txt, haja visto que cada instalação
do ambiente segue características individuais de cada projetista. Sem essas alterações o
código pode não apresentar o comportamento desejado!

A instalação utilizada para construção desta solução, bem como dos testes segue a lógica a seguir:

```cmake
#Versionamento
cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

#Raiz do projeto
project(pico_examples C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.1.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.1.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# If you want debug output from USB (pass -DPICO_STDIO_USB=1) this ensures you don't lose any debug output while USB is set up
if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# Initialize the SDK
pico_sdk_init()

#Adiciona script customizado
include(example_auto_set_url.cmake)

# Adiciona o executável
add_executable(ssd1306_oled_bdl
    src/ssd1306_oled_bdl.c
    src/ssd1306.c
    src/adc_setup.c
    src/i2c_setup.c
    src/oled_setup.c
    src/temperature.c
)

# Diretórios de inclusão
target_include_directories(ssd1306_oled_bdl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Linka as bibliotecas necessárias
target_link_libraries(ssd1306_oled_bdl pico_stdlib hardware_i2c hardware_adc)

# Habilita USB e desabilita UART
pico_enable_stdio_usb(ssd1306_oled_bdl 1)
pico_enable_stdio_uart(ssd1306_oled_bdl 0)

# Gera arquivos extras (map/bin/hex/uf2)
pico_add_extra_outputs(ssd1306_oled_bdl)

# Adiciona URL do projeto
example_auto_set_url(ssd1306_oled_bdl)

if (TARGET hardware_i2c)
    add_subdirectory_exclude_platforms(ssd1306_oled_bdl)
else()
    message("Skipping I2C examples as hardware_i2c is unavailable on this platform")
endif()
```
___
### 🚀 **Apresentação do projeto.**

# 🐣 Eclo Piu-Piu Advanced DMA

Este projeto visa o desenvolvimento de um sistema avançado de controle térmico para incubação de ovos, utilizando um **Raspberry Pi Pico W – Bitdoglab** e técnicas modernas de **DMA (Direct Memory Access) com ADC (Analog-to-Digital Converter)**.

## 🚀 Objetivo do Projeto
O sistema é projetado para pequenos criadores e uso doméstico, garantindo **controle preciso da temperatura** dentro da incubadora. O diferencial desta versão é a utilização do **DMA**, que permite leituras contínuas e eficientes do sensor **PT100**, otimizando a precisão da temperatura e reduzindo a carga da CPU.

## 🔥 Principais Características
- ✅ **Leitura avançada de temperatura**: Uso do **DMA com ADC** para obter leituras de temperatura em alta resolução sem comprometer o desempenho do microcontrolador.
- ✅ **Controle térmico otimizado**: Algoritmo PID ajustável para acionamento de uma resistência elétrica via **PWM**, proporcionando um aquecimento gradual e preciso.
- ✅ **Monitoramento contínuo**: Exibição de temperatura em tempo real em um **display OLED 128x64**.
- ✅ **Automação Inteligente**: Controle de uma ventoinha para circulação de ar e resfriamento quando necessário.
- ✅ **Capacidade**: Incubadora compacta com espaço para **36 ovos**, medindo **20cm de altura, 15cm de largura e 45cm de comprimento**.

## 🛠️ Diferencial: Uso do DMA com ADC
O uso do **DMA** elimina a necessidade de leitura manual do **ADC**, permitindo que os dados de temperatura sejam capturados continuamente e armazenados na memória sem intervenção da CPU. Isso melhora a **precisão** e **eficiência** do controle térmico, garantindo uma incubação mais estável e confiável.

## 📷 Imagem do Projeto
![Eclo Piu-Piu Advanced DMA](EcloPiu-Piu.jpg)

---

🛠 **Desenvolvido por [Seu Nome]**  
📌 *Contribuições são bem-vindas! Sinta-se à vontade para abrir um PR ou relatar issues.* 🚀

___

### 📝 **O código foi desenvolvido em C/C++ e testado no ambiente Bitdoglab.**

### 🔧 **Status**

 🚧 Testado 🟢
___

### 📋 **Lista de Testes que contribuiram para a criação do projeto:**

🟢 Teste 0001 - blink_bdl
🟢 Teste 0002 - button_buzzer_bdl
🟢 Teste 0003 - blink_rgb_bdl
🟢 Teste 0004 - buzzer_bdl
🟢 Teste 0005 - ssd1306_bdl
🟢 Teste 0006 - goertzel_bdl
___
![Projeto final - EcloPiu-Piu](EcloPiu-Piu.jpg)