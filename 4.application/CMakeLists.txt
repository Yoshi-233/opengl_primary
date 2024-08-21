cmake_minimum_required(VERSION 3.10)
project(glfw_test)

#find_package(glfw3 REQUIRED)

set(ROOT_PATH "../")
set(COMMON_INCLUDE "./common/include")
set(INCLUDE_DIRS "${ROOT_PATH}/thirdParty/include")
set(LIBRARY_DIRS "${ROOT_PATH}/thirdParty/lib")
set(GLAD_PATH "${ROOT_PATH}/thirdParty/glad.c")

add_definitions(-DDEBUG_MODE)

include_directories(${INCLUDE_DIRS})
include_directories(${COMMON_INCLUDE})

link_directories(${LIBRARY_DIRS})

add_executable(app main.cpp ${GLAD_PATH})
add_subdirectory(Application)
add_subdirectory(common)

target_link_libraries(app libglfw3.a GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
target_link_libraries(app common application )
