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
