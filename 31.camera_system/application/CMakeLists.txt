# 设置包含目录
include_directories("./include")
include_directories("../common/include")
include_directories("./app/")
include_directories("./camera/include")
include_directories("../glframework/include")

add_library(application app/Application.cpp
        ../common/src/check_err.cpp
        ./camera/camera.cpp
        ./camera/orthographicCamera.cpp
        ./camera/perspectiveCamera.cpp
        ./camera/cameraControl.cpp
        ./camera/trackballCameraController.cpp)