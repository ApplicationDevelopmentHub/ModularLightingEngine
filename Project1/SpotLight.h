#pragma once
#include"Light.h"
#include<glm/glm.hpp>

//PROPERTIES: POS, DIR, COL, INTENSITY, INNER AND OUTER ANGLES
class SpotLight :public Light {
public:
	SpotLight(glm::vec3 pos, glm::vec3 dir,glm::vec3 col,float intensity,float innerAng,float outerAng):
		Light(LightType::Spot),direction(dir),position(pos),color(col),intensity(intensity),
		innerAngle(innerAng),outerAngle(outerAng){ }

	//Light yype field inherired
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	float intensity;
	float innerAngle;
	float outerAngle;
};

