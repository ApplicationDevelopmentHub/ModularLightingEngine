#pragma once
#include"Shadow.h"

class MediumQualityShadow :public Shadow {
public:
	MediumQualityShadow(int resolution,int kernelSize);

	void RenderShadowMap() override;
	unsigned GetShadowTexture() const override;
};
