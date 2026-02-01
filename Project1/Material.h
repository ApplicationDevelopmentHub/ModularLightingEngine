#pragma once

#include <glm/glm.hpp>
#include <cstdint>
#include <glm/common.hpp>

class Material {
public:
	enum class ShadingModel :uint8_t {
		Unlit = 0,
		PBR = 1
	};

	Material(); //constructor

    // ---- Shading model ----
    ShadingModel GetShadingModel() const;
    void SetShadingModel(ShadingModel model);

    // ---- PBR parameters ----
    const glm::vec3& GetAlbedo() const;
    void SetAlbedo(const glm::vec3& color);

    float GetMetallic() const;
    void SetMetallic(float value);

    float GetRoughness() const;
    void SetRoughness(float value);

    float GetAO() const;
    void SetAO(float value);
private:
    // ---- Rendering model ----
    ShadingModel shadingModel = ShadingModel::PBR;

    // ---- PBR core parameters ----
    glm::vec3 albedo{ 0.8f, 0.8f, 0.8f }; // base color
    float     metallic{ 0.0f };             // 0 = dielectric, 1 = metal
    float     roughness{ 0.5f };             // microfacet roughness
    float     ao{ 1.0f };             // ambient occlusion
};
