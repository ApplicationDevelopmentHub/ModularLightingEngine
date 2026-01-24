#pragma once
#include"PrimitiveHandle.h"
#include<unordered_map>
#include<memory>
#include"Primitive.h"

class Scene {
public:
	//Primitives handling
	PrimitiveHandle AddPrimitive(std::unique_ptr<Primitive> primitive); //Only stores primitives

	const std::unordered_map<PrimitiveHandle,
		std::unique_ptr<Primitive>>& GetPrimitives() const;

	//Light handling
private:
	PrimitiveHandle nextPrimitiveId{ 1 };
	std::unordered_map<PrimitiveHandle, std::unique_ptr<Primitive>> primitives;
};
