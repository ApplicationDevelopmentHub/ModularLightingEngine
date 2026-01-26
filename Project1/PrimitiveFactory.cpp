#include"PrimitiveFactory.h"
#include<iostream>

std::unique_ptr<Primitive> PrimitiveFactory::CreatePlane(float size) {
	std::cout << "Primitive factory creating plane." << std::endl;
	return std::make_unique<Plane>(size);
}

std::unique_ptr<Primitive> PrimitiveFactory::CreateSphere(float radius, uint32_t stacks, uint32_t sectors) {
	std::cout << "Primitive factory creating sphere" << std::endl;
	return std::make_unique<Sphere>(radius,stacks,sectors);
}