#pragma once
#include<cstdint>
#include<unordered_map>
#include"Light.h"
#include<memory>
#include"LightFactory.h"
#include"LightData.h"

using LightHandle = uint32_t; //Light id

class LightingSystem {
public:
	LightHandle AddLight(const Lightdata& dat);
	void RemoveLight(LightHandle id);
	const auto GetLights() const;
	const auto GetLight(LightHandle id);
private:
	std::unordered_map<LightHandle, std::unique_ptr<Light>> lights; //maps id to light
	LightHandle nextHandle{ 1 };
};
