cmake_minimum_required(VERSION 3.3)

add_library(ling0
    Parser
    VirtualMachine
)

target_include_directories(ling0
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(ling0
    PRIVATE -Wall -pedantic -Werror
)
