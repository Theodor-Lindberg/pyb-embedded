set(sources RTT/SEGGER_RTT.c
    RTT/SEGGER_RTT_printf.c)

set(lib rtt_lib)
add_library(${lib} ${sources})

target_include_directories(${lib} PUBLIC RTT)
target_include_directories(${lib} PUBLIC Syscalls)

target_compile_definitions(${lib} PUBLIC ${DEVICE_FAMILY})

target_compile_options(${lib} PRIVATE ${opt_level})