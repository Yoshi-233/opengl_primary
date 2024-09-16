//
// Created by Shaozheming on 2024/9/14.
//

#include "include/camera.h"

Camera::~Camera()
= default;

Camera::Camera()
= default;

glm::mat4 Camera::getViewMatrix() const
{
        glm::vec3 front = glm::cross(this->mUp, this->mRight);
        glm::vec3 center = this->mPosition + front;
        return glm::lookAt(this->mPosition, center, this->mUp);;
}

glm::mat4 Camera::getProjectionMatrix() const
{
        return glm::identity<glm::mat4>();
}

