#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

struct SpotLight
{
    // -------- Spatial --------
    glm::vec3 position{ 0.0f, 3.0f, 0.0f };     // world-space position
    float     range{ 20.0f };                   // max influence distance

    glm::vec3 direction{ 0.0f, -1.0f, 0.0f };   // normalized
    float     innerCutoff{ glm::cos(glm::radians(12.5f)) };

    glm::vec3 color{ 1.0f, 1.0f, 1.0f };
    float     outerCutoff{ glm::cos(glm::radians(17.5f)) };

    float intensity{ 1.0f };
    bool  enabled{ true };

    // Padding placeholder (if you later pack into std140 block)
    float _pad0{ 0.0f };
    float _pad1{ 0.0f };

    // -------- Getters / Setters --------
    const glm::vec3& GetPosition() const { return position; }
    void SetPosition(const glm::vec3& p) { position = p; }

    const glm::vec3& GetDirection() const { return direction; }
    void SetDirection(const glm::vec3& d) { direction = glm::normalize(d); }

    const glm::vec3& GetColor() const { return color; }
    void SetColor(const glm::vec3& c) { color = c; }

    float GetIntensity() const { return intensity; }
    void SetIntensity(float i) { intensity = i; }

    float GetInnerCutoff() const { return innerCutoff; }
    void SetInnerCutoffDegrees(float degrees)
    {
        innerCutoff = glm::cos(glm::radians(degrees));
    }

    float GetOuterCutoff() const { return outerCutoff; }
    void SetOuterCutoffDegrees(float degrees)
    {
        outerCutoff = glm::cos(glm::radians(degrees));
    }

    float GetRange() const { return range; }
    void SetRange(float r) { range = r; }

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool e) { enabled = e; }
};
