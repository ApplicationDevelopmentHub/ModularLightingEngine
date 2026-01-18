#pragma once
#include"Shadow.h"

class LowQualityShadow :public Shadow {
public:
	LowQualityShadow(int resoultion,int kernelSize); //constructor

	void RenderShadowMap() override;
	unsigned GetShadowTexture() const override;
};
