#pragma once
#include"LightingSystem.h"

//OBSERVER TO BE USED BY SHADOWS
class ILightObserver {
public:
	virtual ~ILightObserver() = default;

	virtual void OnLightAdded(const LightHandle& id)=0;
	virtual void OnLightRemoved(const LightHandle& id) = 0;
	virtual void OnLightModified(const LightHandle& id) = 0;
};
