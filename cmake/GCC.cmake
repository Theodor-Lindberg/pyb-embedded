# which compilers to use for C and C++
set(CMAKE_C_COMPILER gcc-7)
set(CMAKE_CXX_COMPILER g++-7)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# compiler: language specific flags
set(CMAKE_C_FLAGS "--coverage -fno-builtin -fdata-sections -ffunction-sections" CACHE INTERNAL "c compiler flags")
set(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "c compiler flags: Debug")
set(CMAKE_C_FLAGS_RELEASE "-Os" CACHE INTERNAL "c compiler flags: Release")

set(CMAKE_CXX_FLAGS "--coverage -fno-rtti -fno-exceptions -fno-builtin -fdata-sections -ffunction-sections" CACHE INTERNAL "cxx compiler flags")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "cxx compiler flags: Debug")
set(CMAKE_CXX_FLAGS_RELEASE "-Os" CACHE INTERNAL "cxx compiler flags: Release")