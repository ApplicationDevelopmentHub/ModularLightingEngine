#pragma once
#include<cstdint>
//#include"LightingSystem.h"
using LightHandle = uint32_t; //Light id

//OBSERVER TO BE USED BY SHADOWS
class ILightObserver {
public:
	virtual ~ILightObserver() = default;

	virtual void OnLightAdded(const LightHandle& id)=0;
	virtual void OnLightRemoved(const LightHandle& id) = 0;
	virtual void OnLightModified(const LightHandle& id) = 0;
};
