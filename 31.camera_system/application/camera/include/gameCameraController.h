//
// Created by Shaozheming on 2024/9/16.
//

#ifndef CAMERA_SYSTEM_GAMECAMERACONTROLLER_H
#define CAMERA_SYSTEM_GAMECAMERACONTROLLER_H

#include "cameraControl.h"

class GameCameraController : public CameraControl {
public:
        GameCameraController();

        ~GameCameraController();

public:
        void onCursor(double xPos, double yPos) override;
        void update() override;

        void setSpeed(float speed);

private:
        void pitch(float angle);

        void yaw(float angle);

private:
        float mPitch{0.0f};
        float mSpeed{0.1f};
};

#endif //CAMERA_SYSTEM_GAMECAMERACONTROLLER_H
