#include "Material.h"
#include <algorithm>

// Clamp helper (local, cheap, safe)
static float Clamp01(float v) {
    return std::max(0.0f, std::min(v, 1.0f));
}

Material::Material() = default;

// ---- Shading model ----

Material::ShadingModel Material::GetShadingModel() const {
    return shadingModel;
}

void Material::SetShadingModel(ShadingModel model) {
    shadingModel = model;
}

// ---- Albedo ----

const glm::vec3& Material::GetAlbedo() const {
    return albedo;
}

void Material::SetAlbedo(const glm::vec3& color) {
    albedo = glm::clamp(color, glm::vec3(0.0f), glm::vec3(1.0f));
}

// ---- Metallic ----

float Material::GetMetallic() const {
    return metallic;
}

void Material::SetMetallic(float value) {
    metallic = Clamp01(value);
}

// ---- Roughness ----

float Material::GetRoughness() const {
    return roughness;
}

void Material::SetRoughness(float value) {
    roughness = Clamp01(value);
}

// ---- Ambient Occlusion ----

float Material::GetAO() const {
    return ao;
}

void Material::SetAO(float value) {
    ao = Clamp01(value);
}
