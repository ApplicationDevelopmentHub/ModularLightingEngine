#pragma once
#include"Shadow.h"
#include<memory>
#include"LowQualityShadow.h"
#include"MediumQualityShadow.h"
#include"HighQualityShadow.h"
#include"ShadowType.h"
#include"LightType.h"

class ShadowFactory {
public:
	//static std::unique_ptr<Shadow> CreateShadow(LightType light,ShadowType shadow); //maps shadow to light
};
