#pragma once
#include"Primitive.h"
#include"Mesh.h"
#include<memory>

class Box :public Primitive {
public:
	explicit Box(float length, float width, float height);

	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;
private:
	float length;
	float width;
	float height;
	std::unique_ptr<Mesh> mesh;
};
