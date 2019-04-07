cmake_minimum_required (VERSION 3.10.2)

set(app_name blink)

project(${app_name} C CXX ASM)

# STM32-specific settings
set(DEVICE_FAMILY STM32F405xx)

# Used linker file (just for testing)
get_filename_component(LINKER_SCRIPT linker/stm32f405.ld ABSOLUTE)

# add libraries
add_subdirectory(libs)

# add main project
add_subdirectory(src)