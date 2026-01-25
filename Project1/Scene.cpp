#include"Scene.h"
#include<iostream>

PrimitiveHandle Scene::AddPrimitive(std::unique_ptr<Primitive> primitive) {
	std::cout << "Additive a primitive" << std::endl;
	PrimitiveHandle id = nextPrimitiveId++;
	primitives[id] = std::move(primitive);
	return id;
}

const std::unordered_map<PrimitiveHandle,
	std::unique_ptr<Primitive>>&Scene::GetPrimitives() const {
	return primitives;
}