set(sources src/startup_stm32f405xx.s
    src/system_stm32f4xx.c)

add_library(stm32f4_system ${sources})

target_include_directories(stm32f4_system PUBLIC include)
target_include_directories(stm32f4_system PUBLIC ../../cmsis/include)

target_compile_definitions(stm32f4_system PUBLIC ${DEVICE_FAMILY})

target_compile_options(stm32f4_system PRIVATE -O0)