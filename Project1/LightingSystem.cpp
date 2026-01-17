#include"LightingSystem.h"

LightHandle LightingSystem::AddLight(const Lightdata& dat) {
	auto light = LightFactory::CreateLight(dat);
	LightHandle handle = nextHandle++;
	lights.emplace(handle, std::move(light)); //simple push back or insert copies and creates new memory

	//notify observers
	for (auto* obs : observers) {
		obs->OnLightAdded(handle);
	}

	return handle;
}

void LightingSystem::RemoveLight(LightHandle id) {
	auto it = lights.find(id);
	if (it == lights.end()) return;

	lights.erase(it); //RAII destorys lights safely

	//notify observers
	for (auto* obs : observers) {
		obs->OnLightRemoved(id);
	}
}

void LightingSystem::ModifyLight(LightHandle id,const Lightdata& dat) {
	auto it = lights.find(id);
	if (it == lights.end()) return;

	//modify the light

	//notify observers
	for (auto* obs : observers) {
		obs->OnLightModified(id);
	}
}