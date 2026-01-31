#pragma once
#include"Primitive.h"
#include"Plane.h"
#include"Sphere.h"
#include"Box.h"
#include"Cone.h"

class PrimitiveFactory {
public:
	static std::unique_ptr<Primitive> CreatePlane(float size);
	static std::unique_ptr<Primitive> CreateSphere(float radius, uint32_t stacks, uint32_t sectors);
	static std::unique_ptr<Primitive> CreateBox(float length, float width, float height);
	static std::unique_ptr<Primitive> CreateCone(float radius, float height, uint32_t sectors);
};