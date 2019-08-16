set(sources CatchMain.cpp
            ButtonTest.cpp)

set(test_file ${application_name}_test)
add_executable(${test_file} ${sources})
target_link_libraries(${test_file} PRIVATE app_lib)

target_compile_options(${test_file} PRIVATE ${W_FLAGS} ${TEST_FLAGS})

set(out_directory ../../bin/tests/${CMAKE_BUILD_TYPE}/)

#add_custom_target(make_out_dir ALL
#    COMMAND ${CMAKE_COMMAND} -E make_directory ${out_directory})

#add_custom_command(TARGET ${test_file} 
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${test_file}>  ${out_directory}
#                   COMMENT "Copying to output directory")