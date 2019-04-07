set (sources main.c)

set(elf_file ${app_name}.elf)
set(bin_file ${app_name}.bin)
set(hex_file ${app_name}.hex)
set(map_file ${app_name}.map)
set(lss_file ${app_name}.lss)

add_executable(${elf_file} ${sources})

target_compile_definitions(${elf_file} PUBLIC ${DEVICE_FAMILY})
target_link_libraries(${elf_file} PUBLIC stm32f4_system)

# link with linker file
target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

target_link_libraries(${elf_file} PUBLIC 
"--specs=nano.specs \
  --specs=nosys.specs \
  -mthumb -mcpu=cortex-m4 \
  -Wl,--gc-sections \
  -Wl,-Map=${PROJECT_NAME}.map")

target_compile_options(${elf_file} PUBLIC
  -g
  -O0
  -mthumb
  -mcpu=cortex-m4
  -ffunction-sections 
  -fdata-sections
  -D__STARTUP_CLEAR_BSS
  -D__START=main)

# link with linker file
target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

# show size of resulting firmware image
add_custom_target(${elf_file}-size ALL DEPENDS ${elf_file} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${elf_file})

# generate extended listing
add_custom_target(${lss_file} ALL DEPENDS ${elf_file} COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S ${elf_file} > ${lss_file})

# create binary and hex files
add_custom_target(${hex_file} ALL DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Oihex ${elf_file} ${hex_file})
add_custom_target(${bin_file} ALL DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Obinary ${elf_file} ${bin_file})
add_custom_target(${application_name} ALL DEPENDS ${elf_file}-size ${bin_file} ${hex_file} ${lss_file})