#include"Scene.h"
#include<iostream>

PrimitiveHandle Scene::AddPrimitive(std::unique_ptr<Primitive> primitive) {
	std::cout << "Additive a primitive" << std::endl;
	PrimitiveHandle id{ nextPrimitiveId.value++ };
	primitives[id] = std::move(primitive);
	return id;
}

const std::unordered_map<PrimitiveHandle,
	std::unique_ptr<Primitive>>&Scene::GetPrimitives() const {
	return primitives;
}

Primitive* Scene::GetPrimitive(PrimitiveHandle id) {
	auto it = primitives.find(id);
	if (it == primitives.end())
		return nullptr;

	return it->second.get();
}

void Scene::RemovePrimitive(PrimitiveHandle id) {
	primitives.erase(id);
}

//LIGHTS
//Directional light
LightHandle Scene::AddDirectionalLight(const DirectionalLight& light)
{
	LightHandle id{ nextLightId.value++ };
	directionalLights[id] = light;
	return id;
}

const std::unordered_map<LightHandle, DirectionalLight>&
Scene::GetDirectionalLights() const
{
	return directionalLights;
}

DirectionalLight* Scene::GetDirectionalLight(LightHandle id) {
	auto it = directionalLights.find(id);
	if (it == directionalLights.end())
		return nullptr;

	return &it->second;
}

//Spot light
LightHandle Scene::AddSpotLight(const SpotLight& light) {
	LightHandle id{ nextLightId.value++ };
	spotLights[id] = light;
	return id;
}

SpotLight* Scene::GetSpotLight(LightHandle id) {
	auto it = spotLights.find(id);
	if (it == spotLights.end())
		return nullptr;

	return &it->second;
}

const std::unordered_map<LightHandle, SpotLight>& Scene::GetSpotLights() const {
	return spotLights;
}


//Remove any light by id
void Scene::RemoveLight(LightHandle id)
{
	directionalLights.erase(id);
	spotLights.erase(id);
}
