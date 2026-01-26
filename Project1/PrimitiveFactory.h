#pragma once
#include"Primitive.h"
#include"Plane.h"
#include"Sphere.h"

class PrimitiveFactory {
public:
	static std::unique_ptr<Primitive> CreatePlane(float size);
	static std::unique_ptr<Primitive> CreateSphere(float radius, uint32_t stacks, uint32_t sectors);
};