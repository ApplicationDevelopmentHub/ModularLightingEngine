#pragma once
#include"LightType.h"

class Light {
public:
	~Light() = default; //default destructor compiler generated
	LightType GetType() const { return type; } 
private:
	LightType type;
protected:
	explicit Light(LightType t) :type(t){} //meaning unclear
};
