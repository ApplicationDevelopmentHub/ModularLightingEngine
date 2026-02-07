#pragma once
#include <glm/glm.hpp>

//Properties: Direction, color, intensity
struct DirectionalLight {
    glm::vec3 direction{ -0.2f, -1.0f, -0.3f }; // world-space
    glm::vec3 color{ 1.0f, 1.0f, 1.0f };
    float intensity{ 1.0f };

    // ---- Enable / disable ----
    bool enabled{ true };

    // ---- Getters (engine + inspector friendly) ----
    const glm::vec3& GetDirection() const { return direction; }
    void SetDirection(const glm::vec3& dir) { direction = glm::normalize(dir); }

    const glm::vec3& GetColor() const { return color; }
    void SetColor(const glm::vec3& c) { color = c; }

    float GetIntensity() const { return intensity; }
    void SetIntensity(float i) { intensity = i; }

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool e) { enabled = e; }
};
