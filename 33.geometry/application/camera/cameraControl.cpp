//
// Created by Shaozheming on 2024/9/16.
//

#include "cameraControl.h"
#include "common.h"

CameraControl::~CameraControl()
= default;

void CameraControl::onMouse(int button, int action, double xPos, double yPos)
{
        /* 1. 判断当前按键是否按下 */
        bool isPressed = (action == GLFW_PRESS);

        /* 2. 如果按下，记录位置 */
        if (isPressed) {
                this->mCurrentX = static_cast<float>(xPos);
                this->mCurrentY = static_cast<float>(yPos);
        }

        /* 3. 根据按下的鼠标按键不同，更改按键位置 */
        switch (button) {
                case GLFW_MOUSE_BUTTON_LEFT:
                        this->mLeftMouseDown = isPressed;
                        break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                        this->mMiddleMouseDown = isPressed;
                        break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                        this->mRightMouseDown = isPressed;
                        break;
                default:
                        break;
        }
}

void CameraControl::onCursor(double xPos, double yPos)
{
        INFO("mouse position: ({}, {})", xPos, yPos);
}

void CameraControl::onKey(int key, int action, int mods)
{
        // 过滤repeat
        if (action == GLFW_REPEAT) {
                return;
        }

        /* 1. 判断当前按键是否按下 */
        bool isPressed = (action == GLFW_PRESS);

        /* 2. 记录按键状态 */
        this->mKeyMap[key] = isPressed;
}

void CameraControl::update()
{

}

void CameraControl::setCamera(Camera *camera)
{
        this->mCamera = camera;
}

void CameraControl::setSensitivity(float sensitivity)
{

}

void CameraControl::onScroll(float offset)
{

}

void CameraControl::setScrollSpeed(float speed)
{
        this->mScrollSpeed = speed;
}

CameraControl::CameraControl()
= default;
