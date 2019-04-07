set(CMAKE_SYSTEM_NAME Generic) # 'Generic' is used for embedded systems
set(CMAKE_SYSTEM_VERSION   1)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# tells CMake not to try to link executables during its interal checks
# things are not going to link properly without a linker script
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# find additional toolchain executables
find_program(ARM_SIZE_EXECUTABLE arm-none-eabi-size)
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb)
find_program(ARM_OBJCOPY_EXECUTABLE arm-none-eabi-objcopy)
find_program(ARM_OBJDUMP_EXECUTABLE arm-none-eabi-objdump)