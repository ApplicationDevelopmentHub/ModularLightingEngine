#pragma once
#include<glm/glm.hpp>
#include"LightType.h"

//USE FOR FEEDING LIGHT DATA TO FACTORY 
struct Lightdata
{
    LightType type;

    glm::vec3 position{ 0 };
    glm::vec3 direction{ 0, -1, 0 };
    glm::vec3 color{ 1 };
    float intensity{ 1.0f };

    float range{ 10.0f };        // Point
    float innerAngle{ 0.5f };    // Spot
    float outerAngle{ 0.7f };    // Spot
};
