if(${BUILD_TESTS})
	set(platform desktop)
else()
	set(platform target)
endif()

set(common_src  hal/GPIOBase.cpp
				hal/${platform}/DigitalOut.cpp
				hal/${platform}/DigitalIn.cpp
				hal/${platform}/GPIO.cpp
				utilities/Button.cpp
				utilities/BoardLEDs.cpp
				utilities/BoardButton.cpp
				modbus/ModbusSlaveCom.cpp
				modbus/ModbusRequest.cpp)

set(common_inc  hal
				hal/${platform}
				utilities
				modbus)

if(NOT ${BUILD_TESTS})
	set(sources main.cpp
				hal/${platform}/USART_Driver.cpp
				hal/${platform}/Timer.cpp
				hal/${platform}/HwInitialize.cpp
				modbus/ModbusSlave.cpp)
		
	set(includes modbus)

	# set some project constants
	set(elf_file ${application_name}.elf)
	set(bin_file ${application_name}.bin)
	set(hex_file ${application_name}.hex)
	set(map_file ${application_name}.map)
	set(lss_file ${application_name}.lss)
	set(out_directory ../../../bin/project/${CMAKE_BUILD_TYPE}/)

	add_custom_target(make_out_dir ALL
		COMMAND ${CMAKE_COMMAND} -E make_directory ${out_directory})

	# add sources to elf file
	add_executable(${elf_file} ${sources} ${common_src})
	add_dependencies(${elf_file} make_out_dir)
	target_include_directories(${elf_file} PRIVATE ${includes} ${common_inc})
	target_link_libraries(${elf_file} PRIVATE system_lib hal_lib rtt_lib)

	# set additional for compiler and linker: warnings and generate map file
	set(additional_compiler_flags ${W_FLAGS})
	set(additional_linker_flags -Wl,-Map=${map_file},--cref,--no-warn-mismatch)
	target_compile_options(${elf_file} PRIVATE ${additional_compiler_flags})
	target_link_libraries(${elf_file} PRIVATE ${additional_linker_flags})

	# remove unused sections
	target_link_libraries(${elf_file} PUBLIC "-g -Wl,--gc-sections")

	# link with linker file
	target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

	# show size of resulting firmware image
	add_custom_target(${elf_file}-size DEPENDS ${elf_file} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${elf_file})

	# generate extended listing
	add_custom_target(${lss_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S ${elf_file} > ${lss_file})

	# create binary and hex files
	add_custom_target(${hex_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Oihex ${elf_file} ${hex_file})
	add_custom_target(${bin_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Obinary ${elf_file} ${bin_file})

	# show memory usage
	add_custom_target(${application_name} ALL DEPENDS ${elf_file}-size ${bin_file} ${hex_file} ${lss_file})

	# copy output to the bin directory
	add_custom_command(TARGET ${elf_file} 
				   POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${elf_file}>  ${out_directory}
				   COMMENT "Copying elf file to output directory")

	 add_custom_command(TARGET ${bin_file} 
				   POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy ${bin_file}  ${out_directory}
				   COMMENT "Copying bin file to output directory")

	add_custom_command(TARGET ${hex_file} 
				   POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy ${hex_file}  ${out_directory}
				   COMMENT "Copying bin file to output directory")

	add_custom_command(TARGET ${lss_file} 
				   POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy ${lss_file}  ${out_directory}
				   COMMENT "Copying lss file to output directory")

	add_custom_command(TARGET ${elf_file} 
				   POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy ${map_file}  ${out_directory}
				   COMMENT "Copying map file to output directory")

else()        
	set(lib app_lib)
	add_library(${lib} ${common_src} ./hal/desktop/GPIOState.cpp)
	target_include_directories(${lib} PUBLIC ${common_inc})
	target_compile_options(${lib} PRIVATE ${W_FLAGS} ${TEST_FLAGS})
endif()