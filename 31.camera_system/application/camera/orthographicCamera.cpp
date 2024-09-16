//
// Created by Shaozheming on 2024/9/14.
//

#include "include/orthographicCamera.h"

OrtgographicCamera::OrtgographicCamera(float left, float right, float top, float bottom, float near, float far)
{
        this->mLeft = left;
        this->mRight = right;
        this->mTop = top;
        this->mBottom = bottom;
        this->mNear = near;
        this->mFar = far;
}

OrtgographicCamera::~OrtgographicCamera()
= default;

glm::mat4 OrtgographicCamera::getProjectionMatrix() const
{
        return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}
