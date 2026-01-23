#include"ShadowSystem.h"

//constructor uses lighting system references
ShadowSystem::ShadowSystem(LightingSystem& sys):lightingSystem(sys){}

void ShadowSystem::OnLightAdded(const LightHandle& id) {
	//RUN TIME ERROR: CIRCULAR REFERENCE

	//if (currentShadowQuality == ShadowType::None) return;

	//const Light& light = lightingSystem.GetLight(id);

	////create a new shadow using the shadow factory
	//auto newShadow = ShadowFactory::CreateShadow(light.GetType(),currentShadowQuality);
}

void ShadowSystem::OnLightRemoved(const LightHandle& id) {
	auto it = shadows.find(id);

	if(it!=shadows.end()) shadows.erase(id);
}

void ShadowSystem::OnLightModified(const LightHandle& id) {

}

void ShadowSystem::RenderShadows() {

}