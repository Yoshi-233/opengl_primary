//
// Created by Shaozheming on 2024/9/14.
//

#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
{
       this->mFov = fov;
       this->mAspect = aspect;
       this->mNear = zNear;
       this->mFar = zFar;
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const
{
        return glm::perspective(glm::radians(this->mFov), this->mAspect,
                                this->mNear, this->mFar);
}

void PerspectiveCamera::scale(float deltaScale)
{
        auto front = glm::cross(this->mUp, this->mRight);
        this->mPosition += front * deltaScale;
}

PerspectiveCamera::~PerspectiveCamera()
= default;
