#include"LightFactory.h"
#include"Light.h"
#include"DirectionalLight.h"
#include"PointLight.h"
#include"SpotLight.h"

std::unique_ptr<Light> LightFactory::CreateLight(const Lightdata& dat) {
	switch (dat.type)
	{
		case LightType::Directional:
			return std::make_unique<DirectionalLight>(dat.direction,dat.color,dat.intensity);
			break;
		
		case LightType::Point:
			return std::make_unique<PointLight>(dat.position, dat.color, dat.intensity,dat.range);
			break;

		case LightType::Spot:
			return std::make_unique<SpotLight>(dat.position, dat.direction, dat.color, dat.intensity,
				dat.innerAngle, dat.outerAngle);
			break;

	default:
		return nullptr;
		break;
	}
	return nullptr;
}