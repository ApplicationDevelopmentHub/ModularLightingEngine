#pragma once
#include"Light.h"
#include<memory>
#include"LightData.h"

class LightFactory {
public:
	static std::unique_ptr<Light> CreateLight(const Lightdata& dat);
};
