#pragma once
#include"Light.h"
#include<glm/glm.hpp>

//PROPERTIES: POSITION, COLOR, INTENSITY, RANGE
class PointLight :public Light {
public:
	PointLight(glm::vec3 pos,glm::vec3 col,float intensity,float range):
		Light(LightType::Point),position(pos),color(col),intensity(intensity),range(range){ }

	//Light type field inherited
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float range;
};
