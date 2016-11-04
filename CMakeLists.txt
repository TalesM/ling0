cmake_minimum_required(VERSION 3.3)
project(ling0)

add_subdirectory(src)

add_executable(ling0_prompt
	src_prompt/main
)

target_link_libraries(ling0_prompt
    ling0
)

add_executable(ling0_interpreter
	src_interpreter/main
)

target_link_libraries(ling0_interpreter
    ling0
)

enable_testing()
set(test_base ${CMAKE_SOURCE_DIR}/tests)
FILE(GLOB test_files ${test_base}/*.l0)
foreach(test_file ${test_files})
    string(REGEX MATCH "/([A-Za-z0-9_-]+)\\.l0" ignored ${test_file})
    set(test_name ${CMAKE_MATCH_1})
    set(test_expected ${test_base}/${test_name}.output)
    set(test_result ${test_base}/${test_name}.result)
    add_test(NAME exec_${test_name} COMMAND ling0_interpreter -O${test_result} ${test_file})
    if(EXISTS ${test_expected}) #Allows easier iterating
        add_test(NAME output_${test_name} COMMAND cmake -E compare_files ${test_expected} ${test_result})
    endif()
endforeach(test_file ${test_files})
