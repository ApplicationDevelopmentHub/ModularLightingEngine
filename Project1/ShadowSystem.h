#pragma once
#include"ShadowType.h"
#include"LightingSystem.h"
#include<unordered_map>
#include"Shadow.h"
#include"ILightObserver.h"

//OBSERVER PATTERN: WHEN LIGHT ADDED, REMOVED, OR MODIFIED
class ShadowSystem:public ILightObserver {
public:
	explicit ShadowSystem(LightingSystem& sys);

	void OnLightAdded(const LightHandle& id);
	void OnLightRemoved(const LightHandle& id);
	void OnLightModified(const LightHandle& id);

	void SetShadowQuality(LightHandle id,ShadowType type); //holds same for all the shadows in the scene
	void SetShadowQuality(ShadowType type); //Applies to all

	void RenderShadows(); //Render all shadows recorded yet

private:
	LightingSystem& lightingSystem;
	struct ShadowEntry { // Holds all shadow data: object/container
		std::unique_ptr<Shadow> shadowMode;
		bool dirty = true;
	};

	ShadowType currentShadowQuality;
	std::unordered_map<LightHandle,ShadowEntry> shadows;
};
