#pragma once
#include"Primitive.h"
#include<memory>
#include"Mesh.h"

class Plane:public Primitive {
public:
	explicit Plane(float size);
	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;

	//Modification of primitive
	float GetSize() const;
	void SetSize(float newSize);

	glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& newColor);

	void RebuildMesh();
private:
	float size;
	std::unique_ptr<Mesh> mesh;

	// NEW: real color state (default matches old behavior)
	glm::vec3 color{ 0.8,0.8, 0.8f };

	// NEW: extracted mesh generation logic
	void BuildMesh();
};
