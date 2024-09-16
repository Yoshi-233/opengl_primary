//
// Created by Shaozheming on 2024/9/14.
//

#ifndef CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H
#define CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
        PerspectiveCamera(float fov, float aspect, float zNear, float zFar);
        ~PerspectiveCamera() override = default;

        [[nodiscard]] glm::mat4 getProjectionMatrix() const override;

private:
        float mFov{0.0f};
        float mAspect{0.0f};
        float mNear{0.0f};
        float mFar{0.0f};
};

#endif //CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H
