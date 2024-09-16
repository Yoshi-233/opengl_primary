//
// Created by Shaozheming on 2024/9/16.
//

#ifndef CAMERA_SYSTEM_CAMERACONTROL_H
#define CAMERA_SYSTEM_CAMERACONTROL_H

#include "camera.h"
#include <unordered_map>

class CameraControl {
public:
        CameraControl();

        ~CameraControl();

public:
        /* 处理鼠标事件 */
        virtual void onMouse(int button, int action, double xPos, double yPos);

        virtual void onCursor(double xPos, double yPos);

        virtual void onScroll(float offset);

        /* 处理键盘事件 */
        virtual void onKey(int key, int action, int mods);

        /* update函数，每帧调用 */
        virtual void update();

public:
        /* 设置相机 */
        void setCamera(Camera *camera);

        void setSensitivity(float sensitivity);

        void setScrollSpeed(float speed);
protected:
        /* 鼠标按键状态 */
        bool mLeftMouseDown = false;
        bool mRightMouseDown = false;
        bool mMiddleMouseDown = false;

        /* 当前鼠标位置 */
        float mCurrentX = 0.0f;
        float mCurrentY = 0.0f;

        /* 敏感度 */
        float mSensitivity = 0.2f;
protected:
        /* 记录键盘相关按键的状态 */
        std::unordered_map<int, bool> mKeyMap;
protected:
        /* 存储当前控制的相机 */
        Camera *mCamera{nullptr};
protected:
        /* 记录鼠标滚轮的偏移量 */
        float mScrollSpeed = 0.2f;

};

#endif //CAMERA_SYSTEM_CAMERACONTROL_H
