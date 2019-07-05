set(sources CatchMain.cpp
            ButtonTest.cpp)

set(test_file ${application_name}_test)
add_executable(${test_file} ${sources})
target_link_libraries(${test_file} LINK_PUBLIC app_lib)
target_include_directories(${test_file} PRIVATE ${includes})