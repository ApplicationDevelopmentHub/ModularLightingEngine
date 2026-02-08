#pragma once
#include <glm/glm.hpp>

// Physically based point light (inverse-square falloff friendly)
struct PointLight
{
    // -------- Spatial --------
    glm::vec3 position{ 0.0f, 3.0f, 0.0f };   // world-space position
    float     range{ 25.0f };                 // max influence distance (engine-side clamp)

    // -------- Radiometric --------
    glm::vec3 color{ 1.0f, 1.0f, 1.0f };      // linear color
    float     intensity{ 10.0f };             // luminous power multiplier

    // Optional physically-based emitter radius
    // Helps with specular highlights in PBR (area-light approximation)
    float     radius{ 0.1f };                 // small = sharp highlight
    bool      enabled{ true };

    // Padding for std140 alignment (if packed in UBO)
    float _pad0{ 0.0f };
    float _pad1{ 0.0f };

    // -------- Getters / Setters --------
    const glm::vec3& GetPosition() const { return position; }
    void SetPosition(const glm::vec3& p) { position = p; }

    const glm::vec3& GetColor() const { return color; }
    void SetColor(const glm::vec3& c) { color = c; }

    float GetIntensity() const { return intensity; }
    void SetIntensity(float i) { intensity = i; }

    float GetRange() const { return range; }
    void SetRange(float r) { range = r; }

    float GetRadius() const { return radius; }
    void SetRadius(float r) { radius = glm::max(0.0f, r); }

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool e) { enabled = e; }
};
