//
// Created by Shaozheming on 2024/9/14.
//

#ifndef CAMERA_SYSTEM_CAMERA_H
#define CAMERA_SYSTEM_CAMERA_H

#include "../../../glframework/include/core.h"

class Camera {
public:
        Camera();
        ~Camera();

        [[nodiscard]] glm::mat4 getViewMatrix() const;
        [[nodiscard]] virtual glm::mat4 getProjectionMatrix() const;

        virtual void scale(float deltaScale) = 0;
public:
        glm::vec3 mPosition{0.0f, 0.0f, 1.0f};
        glm::vec3 mUp{0.0f, 1.0f, 0.0f};
        glm::vec3 mRight{1.0f, 0.0f, 0.0f};
};

#endif //CAMERA_SYSTEM_CAMERA_H
