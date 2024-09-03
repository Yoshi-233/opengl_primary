# 设置包含目录
include_directories("./include")
include_directories("../common/include")

file(GLOB_RECURSE GLFRAMEWORK ./ *.cpp)

add_library(glframework ${GLFRAMEWORK})