#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(float aspect)
    : position(0.0f, 2.0f, 6.0f),
    worldUp(0.0f, 1.0f, 0.0f),
    yaw(-90.0f),
    pitch(-15.0f),
    fov(glm::radians(60.0f)),
    aspect(aspect),
    nearPlane(0.1f),
    farPlane(200.0f) {
    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::MoveForward(float amount) {
    position += front * amount;
}

void Camera::MoveBack(float amount) {
    position -= front * amount;
}

void Camera::MoveRight(float amount) {
    position += right * amount;
}

void Camera::MoveLeft(float amount) {
    position -= right * amount;
}

void Camera::MoveUp(float amount) {
    position += worldUp * amount;
}

void Camera::MoveDown(float amount) {
    position -= worldUp * amount;
}

void Camera::RotateRight(float degrees) {
    yaw += degrees;
    UpdateVectors();
}

void Camera::RotateLeft(float degrees) {
    yaw -= degrees;
    UpdateVectors();
}

void Camera::RotateUp(float degrees) {
    pitch += degrees;
    pitch = std::clamp(pitch, -89.0f, 89.0f);
    UpdateVectors();
}

void Camera::RotateDown(float degrees) {
    pitch -= degrees;
    pitch = std::clamp(pitch, -89.0f, 89.0f);
    UpdateVectors();
}

glm::mat4 Camera::GetView() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjection() const {
    return glm::perspective(fov, aspect, nearPlane, farPlane);
}
