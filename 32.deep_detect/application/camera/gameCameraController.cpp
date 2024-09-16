//
// Created by Shaozheming on 2024/9/16.
//

#include "include/gameCameraController.h"

GameCameraController::GameCameraController()
= default;

GameCameraController::~GameCameraController()
= default;

void GameCameraController::setSpeed(float speed)
{
        this->mSpeed = speed;
}

void GameCameraController::onCursor(double xPos, double yPos)
{
        float dx = (static_cast<float>(xPos) - this->mCurrentX) * this->mSensitivity;
        float dy = (static_cast<float>(yPos) - this->mCurrentY) * this->mSensitivity;

        if (this->mRightMouseDown) {
                yaw(-dx);
                pitch(-dy);
        }

        this->mCurrentX = static_cast<float>(xPos);
        this->mCurrentY = static_cast<float>(yPos);
}

void GameCameraController::pitch(float angle)
{
        this->mPitch += angle;
        if (this->mPitch > 89.0f || this->mPitch < -89.0f) {
                this->mPitch -= angle;
                return;
        }
        /* 在game下，并不会影响position, 角度在-90 90之间 */
        auto rotateMatrix = glm::rotate(glm::mat4(1.0f),
                                        glm::radians(angle),
                                        this->mCamera->mRight);
        this->mCamera->mUp = rotateMatrix * glm::vec4(this->mCamera->mUp, 0.0f);
}

void GameCameraController::yaw(float angle)
{
        auto rotateMatrix = glm::rotate(glm::mat4(1.0f),
                                        glm::radians(angle),
                                        glm::vec3(0.0f, 1.0f, 0.0f));

        this->mCamera->mRight = rotateMatrix * glm::vec4(this->mCamera->mRight, 0.0f);
        this->mCamera->mUp = rotateMatrix * glm::vec4(this->mCamera->mUp, 0.0f);
}

void GameCameraController::update()
{
        // 最终移动方向
        auto direction = glm::vec3(0.0f);

        auto front = glm::cross(this->mCamera->mUp, this->mCamera->mRight);
        auto right = this->mCamera->mRight;

        if (this->mKeyMap[GLFW_KEY_W]) {
                direction += front;
        }

        if (this->mKeyMap[GLFW_KEY_S]) {
                direction -= front;
        }

        if (this->mKeyMap[GLFW_KEY_A]) {
                direction -= right;
        }

        if (this->mKeyMap[GLFW_KEY_D]) {
                direction += right;
        }

        // 此时direction有可能为0
        if (glm::length(direction) != 0.0f) {
                direction = glm::normalize(direction);
                this->mCamera->mPosition += direction * this->mSpeed;
        }
}


