cmake_minimum_required (VERSION 3.10.2)
message("Build type: " ${CMAKE_BUILD_TYPE})
message("Build tests: " ${build_tests})

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    message("No build type selected, choosing Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(opt_level -O0)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  set(opt_level -Os)
else()
  message(SEND_ERROR "Unkown build type")
endif()

# STM32-specific settings
set(DEVICE_FAMILY STM32F405xx)

# Project specific settings
set(application_name "proj")

if(NOT ${build_tests})
  project(${application_name} C CXX ASM)
  get_filename_component(LINKER_SCRIPT linker/stm32f407vgt.ld ABSOLUTE)

  # add libraries
  add_subdirectory(libs)

  # add main project
  add_subdirectory(src)
else()
  project(${application_name} C CXX)

  # add main project as a library
  add_subdirectory(src)
  add_subdirectory(tests)
endif()