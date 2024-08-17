cmake_minimum_required(VERSION 3.12)

project(test)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(funcs)
# Add source files
#aux_source_directory(. SRC_LIST)

add_executable(test main.cpp)

target_link_libraries(test funcs)
