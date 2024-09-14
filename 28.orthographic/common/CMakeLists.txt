# common/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# 添加包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加库源文件
add_library(common STATIC
        ./src/check_err.cpp
        ./src/common.cpp
)
