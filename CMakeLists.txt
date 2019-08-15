cmake_minimum_required (VERSION 3.10.2)
message("Build type: " ${CMAKE_BUILD_TYPE})
message("Build tests: " ${build_tests})

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    message("No build type selected, choosing Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

# STM32-specific settings
set(DEVICE_FAMILY STM32F405xx)

# Project specific settings
set(application_name "proj")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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