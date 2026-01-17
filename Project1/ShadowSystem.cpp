#include"ShadowSystem.h"

//constructor uses lighting system references
ShadowSystem::ShadowSystem(LightingSystem& sys):lightingSystem(sys){}

void ShadowSystem::OnLightAdded(const LightHandle& id) {
	if (currentShadowQuality == ShadowType::None) return;

	const Light& light = lightingSystem.GetLight(id);

	//create a new shadow using the shadow factory
}

void ShadowSystem::OnLightRemoved(const LightHandle& id) {

}

void ShadowSystem::OnLightModified(const LightHandle& id) {

}

void ShadowSystem::RenderShadows() {

}