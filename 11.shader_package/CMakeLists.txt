cmake_minimum_required(VERSION 3.10)
set(PROJ_NAME "shader")
project(${PROJ_NAME})

# 外部资源copy cmake
file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

set(ROOT_PATH "../")
set(COMMON_INCLUDE "./common/include")
set(INCLUDE_DIRS "${ROOT_PATH}/thirdParty/include")
set(LIBRARY_DIRS "${ROOT_PATH}/thirdParty/lib")
set(GLAD_PATH "${ROOT_PATH}/thirdParty/glad.c")

add_definitions(-DDEBUG_MODE)

include_directories(${INCLUDE_DIRS})
include_directories(${COMMON_INCLUDE})

link_directories(${LIBRARY_DIRS})

add_subdirectory(application)
add_subdirectory(common)
add_subdirectory(glframework)

add_executable(${PROJ_NAME} main.cpp ${GLAD_PATH})
target_link_libraries(${PROJ_NAME} libglfw3.a GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
target_link_libraries(${PROJ_NAME} common application glframework libspdlog.a)


