cmake_minimum_required (VERSION 3.10.2)

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
endif()

# Project specific settings
set(application_name "blink")

project (${application_name} C CXX ASM)

# STM32-specific settings
set(DEVICE_FAMILY STM32F405xx)

# Used linker file (just for testing)
get_filename_component(LINKER_SCRIPT linker/stm32f407vgt.ld ABSOLUTE)

# additional compiler options: use size-optimized version of library in release build, use -O0 in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(opt_level -O0)
else()
  set(opt_level -Os)
endif()

# add libraries
add_subdirectory(libs)

# add main project
add_subdirectory(src)