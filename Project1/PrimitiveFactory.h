#pragma once
#include"Primitive.h"
#include"Plane.h"

class PrimitiveFactory {
public:
	static std::unique_ptr<Primitive> CreatePlane(float size);
};