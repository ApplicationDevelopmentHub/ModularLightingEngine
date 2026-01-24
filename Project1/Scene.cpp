#include"Scene.h"

PrimitiveHandle Scene::AddPrimitive(std::unique_ptr<Primitive> primitive) {
	PrimitiveHandle id = nextPrimitiveId++;
	primitives[id] = std::move(primitive);
	return id;
}

const std::unordered_map<PrimitiveHandle,
	std::unique_ptr<Primitive>>&Scene::GetPrimitives() const {
	return primitives;
}