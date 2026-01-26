#pragma once
#include"Primitive.h"
#include<memory>
#include"Mesh.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Sphere :public Primitive {
public:
	explicit Sphere(float radius, uint32_t stacks, uint32_t sectors);
	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;
private:
	std::unique_ptr<Mesh> mesh;
};