#pragma once
#include"Primitive.h"
#include<memory>
#include"Mesh.h"

class Plane:public Primitive {
public:
	explicit Plane(float size);
	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;
private:
	std::unique_ptr<Mesh> mesh;
};
