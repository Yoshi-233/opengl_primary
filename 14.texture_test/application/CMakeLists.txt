# 设置包含目录
include_directories("./include")
include_directories("../common/include")

add_library(application Application.cpp ../common/src/check_err.cpp)