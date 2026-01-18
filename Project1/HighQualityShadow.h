#pragma once
#include"Shadow.h"

class HighQualityShadow :public Shadow {
public:
	HighQualityShadow(int resolution, int kernelSize);

	void RenderShadowMap() override;
	unsigned GetShadowTexture() const override;
};
