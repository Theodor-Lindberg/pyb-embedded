set(sources src/startup_stm32f405xx.s
    src/system_stm32f4xx.c)

set(includes inc
            ../../cmsis/inc)

set(lib system_lib)
add_library(${lib} ${sources})

target_include_directories(${lib} SYSTEM PUBLIC ${includes})

target_compile_definitions(${lib} PUBLIC ${DEVICE_FAMILY} ${OSCILLATOR_SETTINGS})