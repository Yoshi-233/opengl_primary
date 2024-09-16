//
// Created by Shaozheming on 2024/9/14.
//

#ifndef CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H
#define CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H

#include "camera.h"

class OrtgographicCamera : public Camera {
public:
        OrtgographicCamera(float left, float right, float top, float bottom, float near, float far);
        ~OrtgographicCamera() override;

        [[nodiscard]] glm::mat4 getProjectionMatrix() const override;
private:
        float mLeft{0.0f};
        float mRight{0.0f};
        float mTop{0.0f};
        float mBottom{0.0f};
        float mNear{0.0f};
        float mFar{0.0f};
};

#endif //CAMERA_SYSTEM_ORTGOGRAPHICCAMERA_H
