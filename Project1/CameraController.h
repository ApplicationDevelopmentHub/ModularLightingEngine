#pragma once
#include "Camera.h"

class CameraController {
public:
    explicit CameraController(Camera& camera);

    void Update(float deltaTime);

private:
    Camera& camera;

    float moveSpeed = 5.0f;
    float rotationSpeed = 60.0f;
};
