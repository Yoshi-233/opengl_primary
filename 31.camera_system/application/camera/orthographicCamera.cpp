//
// Created by Shaozheming on 2024/9/14.
//

#include "include/orthographicCamera.h"
#include "common.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
{
        this->mLeft = left;
        this->mRight = right;
        this->mTop = top;
        this->mBottom = bottom;
        this->mNear = near;
        this->mFar = far;
}

OrthographicCamera::~OrthographicCamera()
= default;

glm::mat4 OrthographicCamera::getProjectionMatrix() const
{
        float scale = glm::pow(2.0f, this->mScale);
        // 不需要缩放远和近平面，三角形可能被剪裁
        return glm::ortho(mLeft * scale, mRight * scale,
                          mBottom * scale, mTop * scale,
                          mNear, mFar);
}

void OrthographicCamera::scale(float deltaScale)
{
        this->mScale -= deltaScale;
}
