cmake_minimum_required(VERSION 3.10)
project(glfw_test)

find_package(glfw3 REQUIRED)

include_directories(
        SYSTEM ../thirdParty/include
)

link_directories(
        ../thirdParty/lib
)

add_executable(glfw_test main.cpp ../glad.c)

target_link_libraries(glfw_test libglfw3.a GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
