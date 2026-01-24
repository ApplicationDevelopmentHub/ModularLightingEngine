#include"PrimitiveFactory.h"

std::unique_ptr<Primitive> PrimitiveFactory::CreatePlane(float size) {
	return std::make_unique<Plane>(size);
}