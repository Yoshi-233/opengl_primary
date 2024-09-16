//
// Created by Shaozheming on 2024/9/16.
//

#include "trackballCameraController.h"
#include "common.h"

TrackballCameraController::TrackballCameraController()
= default;

TrackballCameraController::~TrackballCameraController()
= default;

void TrackballCameraController::onCursor(double xPos, double yPos)
{
        if (this->mCamera == nullptr) {
                ERROR("camera is nullptr");
                return;
        }

        // 只有点住右键才会有旋转效果
        if (this->mRightMouseDown) {
                /* 1.计算经线和纬线旋转角度 */
                float dx = (static_cast<float>(xPos) - this->mCurrentX) * this->mSensitivity;
                float dy = (static_cast<float>(yPos) - this->mCurrentY) * this->mSensitivity;

                /* 2.分开pitch(俯仰角)和yaw(偏航角)分别计算 */
                // INFO("dx {} dy {}", dx, dy);
                yaw(-dx);
                pitch(-dy);
        }

        if (this->mMiddleMouseDown) {
                float dx = (static_cast<float>(xPos) - this->mCurrentX) * this->mMoveSpeed;
                float dy = (static_cast<float>(yPos) - this->mCurrentY) * this->mMoveSpeed;

                this->mCamera->mPosition += this->mCamera->mUp * dy;
                this->mCamera->mPosition -= this->mCamera->mRight * dx;
        }

        /* 更新位置 */
        this->mCurrentX = static_cast<float>(xPos);
        this->mCurrentY = static_cast<float>(yPos);
}

void TrackballCameraController::yaw(float angle)
{
        /* 旋转是绕世界坐标的y轴旋转 */
        auto rotateMatrix = glm::rotate(glm::mat4(1.0f),
                                        glm::radians(angle),
                                        glm::vec3(0.0f, 1.0f, 0.0f));

        this->mCamera->mPosition = rotateMatrix * glm::vec4(this->mCamera->mPosition, 1);
        this->mCamera->mUp = rotateMatrix * glm::vec4(this->mCamera->mUp, 0);
        this->mCamera->mRight = rotateMatrix * glm::vec4(this->mCamera->mRight, 0);
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

        // 下面不需要，因为绕着mRight旋转，mRight不会改变
        // this->mCamera->mRight = rotateMatrix * glm::vec4(this->mCamera->mRight, 0);
        // INFO(glm::to_string(this->mCamera->mRight));
}

void TrackballCameraController::onScroll(float offset)
{
        if (this->mCamera == nullptr) {
                ERROR("camera is nullptr");
                return;
        }

        this->mCamera->scale(offset * this->mScrollSpeed);
}
