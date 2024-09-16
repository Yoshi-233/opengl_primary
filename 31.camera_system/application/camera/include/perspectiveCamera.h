//
// Created by Shaozheming on 2024/9/14.
//
#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
        PerspectiveCamera(float fov, float aspect, float zNear, float zFar);
        ~PerspectiveCamera();

        [[nodiscard]] glm::mat4 getProjectionMatrix() const override;
        void scale(float deltaScale) override;

private:
        float mFov{0.0f};
        float mAspect{0.0f};
        float mNear{0.0f};
        float mFar{0.0f};
};

