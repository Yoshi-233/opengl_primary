cmake_minimum_required(VERSION 3.10)
project(glfw_test)

find_package(glfw3 REQUIRED)

set(INCLUDE_DIRS "/home/shao/opengl_projects/thirdParty/include")
set(LIBRARY_DIRS "/home/shao/opengl_projects/thirdParty/lib")
set(GLAD_PATH "/home/shao/opengl_projects/glad.c")

add_definitions(-DDEBUG_MODE)

include_directories(${INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../common/include)
add_library(common STATIC
        ${CMAKE_SOURCE_DIR}/../common/src/check_err.cpp
)
link_directories(${LIBRARY_DIRS})

add_executable(glad_test main.cpp ${GLAD_PATH})

target_link_libraries(glad_test libglfw3.a GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
target_link_libraries(glad_test common)
