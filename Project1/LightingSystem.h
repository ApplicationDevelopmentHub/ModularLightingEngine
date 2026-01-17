#pragma once
#include<cstdint>
#include<unordered_map>
#include"Light.h"
#include<memory>
#include"LightFactory.h"
#include"LightData.h"
#include"ILightObserver.h"

using LightHandle = uint32_t; //Light id

class LightingSystem {
public:
	LightHandle AddLight(const Lightdata& dat);
	void RemoveLight(LightHandle id);
	void ModifyLight(LightHandle id,const Lightdata& dat);

	const auto GetLights() const;
	const auto GetLight(LightHandle id);

	//Register and unregister observers
	//raw pointers
	//Obs do not own subject and vice versa
	void RegisterObserver(ILightObserver* obs);
	void UnregisterObserver(ILightObserver* obs);
private:
	std::unordered_map<LightHandle, std::unique_ptr<Light>> lights; //maps id to light
	LightHandle nextHandle{ 1 };
	std::vector<ILightObserver*> observers;
};

