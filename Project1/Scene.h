#pragma once
#include"PrimitiveHandle.h"
#include"LightHandle.h"
#include<unordered_map>
#include<memory>
#include"Primitive.h"
#include"DirectionalLight.h"
#include"SpotLight.h"
#include"PointLight.h"

class Scene {
public:
	//PRIMITIVES
	PrimitiveHandle AddPrimitive(std::unique_ptr<Primitive> primitive); //Only stores primitives

	const std::unordered_map<PrimitiveHandle,
		std::unique_ptr<Primitive>>& GetPrimitives() const;

	Primitive* GetPrimitive(PrimitiveHandle id);

	void RemovePrimitive(PrimitiveHandle id);

	//LIGHTS

	//Directional light
	LightHandle AddDirectionalLight(const DirectionalLight& light);
	DirectionalLight* GetDirectionalLight(LightHandle id);
	const std::unordered_map<LightHandle, DirectionalLight>&
		GetDirectionalLights() const;

	//Spot light
	LightHandle AddSpotLight(const SpotLight& light);
	SpotLight* GetSpotLight(LightHandle id);
	const std::unordered_map<LightHandle, SpotLight>& GetSpotLights() const;

	//Point light
	LightHandle AddpointLight(const PointLight& light);
	PointLight* GetPointLight(LightHandle id);
	const std::unordered_map<LightHandle, PointLight>& GetPointLights() const;

	//Remove any light by id
	void RemoveLight(LightHandle id);

private:
	//PRIMITIVES
	PrimitiveHandle nextPrimitiveId{ 1 };
	std::unordered_map<PrimitiveHandle, std::unique_ptr<Primitive>> primitives;

	//LIGHTS
	LightHandle     nextLightId{ 1 };
	std::unordered_map<LightHandle, DirectionalLight> directionalLights;
	std::unordered_map<LightHandle, PointLight>       pointLights;
	std::unordered_map<LightHandle, SpotLight>        spotLights;
};
