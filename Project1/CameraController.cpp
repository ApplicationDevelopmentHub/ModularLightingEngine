#include "CameraController.h"
#include "Input.h"
#include <GLFW/glfw3.h>

CameraController::CameraController(Camera& cam)
    : camera(cam) {
}

void CameraController::Update(float deltaTime) {
    float move = moveSpeed * deltaTime;
    float rot = rotationSpeed * deltaTime;

    if (Input::IsKeyDown(GLFW_KEY_W)) camera.MoveForward(move);
    if (Input::IsKeyDown(GLFW_KEY_S)) camera.MoveBack(move);
    if (Input::IsKeyDown(GLFW_KEY_A)) camera.MoveLeft(move);
    if (Input::IsKeyDown(GLFW_KEY_D)) camera.MoveRight(move);

    if (Input::IsKeyDown(GLFW_KEY_UP))    camera.RotateUp(rot);
    if (Input::IsKeyDown(GLFW_KEY_DOWN))  camera.RotateDown(rot);
    if (Input::IsKeyDown(GLFW_KEY_LEFT))  camera.RotateLeft(rot);
    if (Input::IsKeyDown(GLFW_KEY_RIGHT)) camera.RotateRight(rot);
}