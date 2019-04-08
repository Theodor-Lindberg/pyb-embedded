set(sources src/startup_stm32f405xx.s
    src/system_stm32f4xx.c)

set(system_lib stm32f4_system)
add_library(${system_lib} ${sources})

target_include_directories(${system_lib} PUBLIC include)
target_include_directories(${system_lib} PUBLIC ../../cmsis/include)

target_compile_definitions(${system_lib} PUBLIC ${DEVICE_FAMILY})

# additional compiler options: use size-optimized version of library in release build, use -O0 in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -Os)
endif()

target_compile_options(${system_lib} PRIVATE ${additional_flags})
