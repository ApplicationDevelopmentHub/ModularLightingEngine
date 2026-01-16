#pragma once
#include"LightType.h"

class Light {
public:
	~Light() = default;
	LightType GetType() const { return type; }
private:
	LightType type;
protected:
	explicit Light(LightType t) :type(t){} //meaning unclear
};
