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
FILE(GLOB test_files ${CMAKE_SOURCE_DIR}/tests/*.l0)
foreach(test_file ${test_files})
    string(REGEX MATCH "/([A-Za-z0-9_-]+)\\.l0" ignored ${test_file})
    set(test_name ${CMAKE_MATCH_1})
    add_test(NAME blackbox_${test_name} COMMAND ling0_interpreter ${test_file})
endforeach(test_file ${test_files})
