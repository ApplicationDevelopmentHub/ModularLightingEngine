#pragma once
#include"Light.h"
#include<glm/glm.hpp>

//PROPERTIES: DIRECTION, COLOR, INTENSITY
class DirectionalLight :public Light {
public:
	DirectionalLight(glm::vec3 dir, glm::vec3 col, float intensity) :
		Light(LightType::Directional),direction(dir),color(col),intensity(intensity){}

	//Light Type field already inherited from the base class:: to be added in constructor
	glm::vec3 direction;
	glm::vec3 color;
	float intensity;
};
