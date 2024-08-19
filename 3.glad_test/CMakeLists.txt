cmake_minimum_required(VERSION 3.10)
project(glfw_test)

#find_package(glfw3 REQUIRED)

set(INCLUDE_DIRS "../thirdParty/include")
set(LIBRARY_DIRS "../thirdParty/lib")
set(GLAD_PATH "../glad.c")

add_definitions(-DDEBUG_MODE)

include_directories(${INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/../common/include)

link_directories(${LIBRARY_DIRS})

add_subdirectory(common)
add_executable(glad_test main.cpp ${GLAD_PATH})

target_link_libraries(glad_test libglfw3.a GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
target_link_libraries(glad_test common)
