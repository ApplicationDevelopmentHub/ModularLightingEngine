#pragma once
#include"PrimitiveHandle.h"
#include"LightHandle.h"
#include<unordered_map>
#include<memory>
#include"Primitive.h"
#include"DirectionalLight.h"

class Scene {
public:
	//PRIMITIVES
	PrimitiveHandle AddPrimitive(std::unique_ptr<Primitive> primitive); //Only stores primitives

	const std::unordered_map<PrimitiveHandle,
		std::unique_ptr<Primitive>>& GetPrimitives() const;

	Primitive* GetPrimitive(PrimitiveHandle id);

	void RemovePrimitive(PrimitiveHandle id);

	//LIGHTS
	LightHandle AddDirectionalLight(const DirectionalLight& light);
	void RemoveLight(LightHandle id);
	DirectionalLight* GetDirectionalLight(LightHandle id);
	const std::unordered_map<LightHandle, DirectionalLight>&
		GetDirectionalLights() const;

private:
	//PRIMITIVES
	PrimitiveHandle nextPrimitiveId{ 1 };
	std::unordered_map<PrimitiveHandle, std::unique_ptr<Primitive>> primitives;

	//LIGHTS
	LightHandle     nextLightId{ 1 };
	std::unordered_map<LightHandle, DirectionalLight> directionalLights;
	/*std::unordered_map<LightHandle, PointLight>       pointLights;
	std::unordered_map<LightHandle, SpotLight>        spotLights;*/
};
