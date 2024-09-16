//
// Created by Shaozheming on 2024/9/16.
//

#ifndef CAMERA_SYSTEM_TRACKBALLCAMERACONTROLLER_H
#define CAMERA_SYSTEM_TRACKBALLCAMERACONTROLLER_H

#include "cameraControl.h"

class TrackballCameraController : public CameraControl {
public:
        TrackballCameraController();

        ~TrackballCameraController() override;
public:
        void onCursor(double xPos, double yPos) override;
private:
        void pitch(float angle);
        void yaw(float angle);
private:
        float mMoveSpeed = 0.005f;
};

#endif //CAMERA_SYSTEM_TRACKBALLCAMERACONTROLLER_H
