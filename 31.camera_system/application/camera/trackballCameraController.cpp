//
// Created by Shaozheming on 2024/9/16.
//

#include "trackballCameraController.h"
#include "common.h"

TrackballCameraController::TrackballCameraController()
{

}

TrackballCameraController::~TrackballCameraController()
= default;

void TrackballCameraController::onCursor(double xPos, double yPos)
{
        INFO("TrackballCameraController::onCursor {} {} {}", xPos, yPos, this->mRightMouseDown);
        // 只有点住右键才会有旋转效果
        if (this->mRightMouseDown) {
                /* 1.计算经线和纬线旋转角度 */
                float dx = (static_cast<float>(xPos) - this->mCurrentX) * this->mSensitivity;
                float dy = (static_cast<float>(yPos) - this->mCurrentY) * this->mSensitivity;

                /* 2.分开pitch(俯仰角)和yaw(偏航角)分别计算 */
                pitch(dy);
        }

        /* 更新位置 */
        this->mCurrentX = static_cast<float>(xPos);
        this->mCurrentY = static_cast<float>(yPos);
}

void TrackballCameraController::yaw(float angle)
{

}

void TrackballCameraController::pitch(float angle)
{
        /* 旋转是绕mRight旋转 */
        auto rotateMatrix = glm::rotate(glm::mat4(1.0f),
                               glm::radians(angle),
                               this->mCamera->mRight);

        // vec4最后一个维度补0为齐次坐标，代表向量
        // 补充1为点, 除以第四个维度
        // vec4强转成vec3，去掉齐次坐标
        this->mCamera->mUp = rotateMatrix * glm::vec4(this->mCamera->mUp, 0);
        this->mCamera->mPosition = rotateMatrix * glm::vec4(this->mCamera->mPosition, 1);
}
