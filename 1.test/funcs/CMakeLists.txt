# 递归将当前目录下的所有.cpp文件编译成一个名为funcs的库
file(GLOB_RECURSE FUNCS ./ *.cpp)

# 编译成静态库
add_library(funcs ${FUNCS})