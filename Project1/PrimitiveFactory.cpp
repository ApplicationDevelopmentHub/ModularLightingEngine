#include"PrimitiveFactory.h"
#include<iostream>

std::unique_ptr<Primitive> PrimitiveFactory::CreatePlane(float size) {
	std::cout << "Primitive factory" << std::endl;
	return std::make_unique<Plane>(size);
}