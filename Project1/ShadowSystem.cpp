#include"ShadowSystem.h"

//constructor uses lighting system references
ShadowSystem::ShadowSystem(LightingSystem& sys):lightingSystem(sys){}

void ShadowSystem::OnLightAdded(const LightHandle& id) {
	if (currentShadowQuality == ShadowType::None) return;

	const Light& light = lightingSystem.GetLight(id);
}

void ShadowSystem::OnLightRemoved(const LightHandle& id) {

}

void ShadowSystem::OnLightModified(const LightHandle& id) {

}

void ShadowSystem::RenderShadows() {

}