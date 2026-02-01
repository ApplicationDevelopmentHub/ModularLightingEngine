#include"Scene.h"
#include<iostream>

PrimitiveHandle Scene::AddPrimitive(std::unique_ptr<Primitive> primitive) {
	std::cout << "Additive a primitive" << std::endl;
	PrimitiveHandle id{ nextPrimitiveId.value++ };
	primitives[id] = std::move(primitive);
	return id;
}

const std::unordered_map<PrimitiveHandle,
	std::unique_ptr<Primitive>>&Scene::GetPrimitives() const {
	return primitives;
}

Primitive* Scene::GetPrimitive(PrimitiveHandle id) {
	auto it = primitives.find(id);
	if (it == primitives.end())
		return nullptr;

	return it->second.get();
}

void Scene::RemovePrimitive(PrimitiveHandle id) {
	primitives.erase(id);
}