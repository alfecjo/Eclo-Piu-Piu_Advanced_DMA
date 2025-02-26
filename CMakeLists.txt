# Adiciona o executável
add_executable(dma_eclopiupiu_bdl
    src/dma_eclopiupiu_bdl.c
    src/ssd1306.c
    src/adc_setup_dma.c
    src/i2c_setup.c
    src/oled_setup.c
    src/temperature.c
)

# Diretórios de inclusão
target_include_directories(dma_eclopiupiu_bdl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Linka as bibliotecas necessárias
target_link_libraries(dma_eclopiupiu_bdl 
    pico_stdlib
    hardware_i2c
    hardware_adc
    hardware_dma)

# Habilita USB e desabilita UART
pico_enable_stdio_usb(dma_eclopiupiu_bdl 1)
pico_enable_stdio_uart(dma_eclopiupiu_bdl 0)

# Gera arquivos extras (map/bin/hex/uf2)
pico_add_extra_outputs(dma_eclopiupiu_bdl)

# Adiciona URL do projeto
example_auto_set_url(dma_eclopiupiu_bdl)