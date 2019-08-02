set(sources src/stm32f4xx_ll_adc.c
    src/stm32f4xx_ll_crc.c
    src/stm32f4xx_ll_dac.c
    src/stm32f4xx_ll_dma.c
    src/stm32f4xx_ll_dma2d.c
    src/stm32f4xx_ll_exti.c
    src/stm32f4xx_ll_fmc.c
    src/stm32f4xx_ll_fsmc.c
    src/stm32f4xx_ll_gpio.c
    src/stm32f4xx_ll_i2c.c
    src/stm32f4xx_ll_lptim.c
    src/stm32f4xx_ll_pwr.c
    src/stm32f4xx_ll_rcc.c
    src/stm32f4xx_ll_rng.c
    src/stm32f4xx_ll_rtc.c
    src/stm32f4xx_ll_sdmmc.c
    src/stm32f4xx_ll_spi.c
    src/stm32f4xx_ll_tim.c
    src/stm32f4xx_ll_usart.c
    src/stm32f4xx_ll_usb.c
    src/stm32f4xx_ll_utils.c)

set(includes inc
    ../system/inc 
    ../../cmsis/inc)

set(lib hal_lib)
add_library(${lib} ${sources})

target_include_directories(${lib} PUBLIC ${includes})

target_compile_definitions(${lib} PUBLIC ${DEVICE_FAMILY} USE_FULL_LL_DRIVER)

target_compile_options(${lib} PRIVATE ${opt_level})