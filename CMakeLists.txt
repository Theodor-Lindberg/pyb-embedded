cmake_minimum_required (VERSION 3.10.2)

# Options
option(BUILD_TESTS "Build unit tests" OFF)
option(ENABLE_COVERAGE "Generate test coverage" OFF)
option(GEN_DOCS "Generate documentation" OFF)

message("Build type: " ${CMAKE_BUILD_TYPE})
message("Build tests: " ${BUILD_TESTS})
message("Run with test coverage: " ${ENABLE_COVERAGE})
message("Generate documentation: " ${GEN_DOCS})

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    message("No build type selected, choosing Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

# STM32-specific settings
set(DEVICE_FAMILY STM32F405xx)

# Project specific settings
set(application_name "proj")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT ${BUILD_TESTS})
  project(${application_name} C CXX ASM)
  get_filename_component(LINKER_SCRIPT linker/stm32f407vgt.ld ABSOLUTE)

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(W_FLAGS -Wpedantic -Wall -Wextra -Wcast-align -Wunused -Wundef -Wconversion -Wdouble-promotion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -fno-common -Wnull-dereference -Wuseless-cast -Wold-style-cast -Wredundant-decls -Wundef -Wno-unused -Wsuggest-final-types -Wsuggest-override -Woverloaded-virtual)
  endif()

  # add libraries
  add_subdirectory(third_party)

  # add main project
  add_subdirectory(src)
else()
  project(${application_name} C CXX)

  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(${ENABLE_COVERAGE})
      set(TEST_FLAGS --coverage)
      set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
      set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
    endif()
  endif()

  # add main project as a library
  add_subdirectory(src)
  add_subdirectory(tests)
endif()

# Generate Doxygen documentation
if (GEN_DOCS)
    add_subdirectory(docs)
endif (GEN_DOCS)