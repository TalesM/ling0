cmake_minimum_required(VERSION 3.3)

add_library(ling0
    Context
)

target_include_directories(ling0
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
