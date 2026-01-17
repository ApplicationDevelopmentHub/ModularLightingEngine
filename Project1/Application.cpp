#include"Application.h"

void Application::Init() {
	lightingSystem = std::make_unique<LightingSystem>();
	shadowSystem = std::make_unique<ShadowSystem>();
	lightingSystem->RegisterObserver(shadowSystem.get());
}

LightHandle Application::AddLight(const Lightdata& dat) {
	return lightingSystem->AddLight(dat);
}
void Application::RemoveLight(LightHandle id){
	lightingSystem->RemoveLight(id);
}