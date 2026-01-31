#pragma once
#include"Primitive.h"
#include"Mesh.h"
#include<memory>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Cone:public Primitive {
public:
	explicit Cone(float radius, float height, uint32_t sectors);
	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;

	//Shape modification
	std::uint32_t GetHeight() const;
	void SetHeight(std::uint32_t stack);

	std::uint32_t GetSectors() const;
	void SetSectors(std::uint32_t sector);

	float GetRadius() const;
	void SetRadius(float radVal);

	glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& newColor);

	const glm::vec3& GetPosition() const;
	void SetPosition(const glm::vec3& p);

	void RebuildMesh();
private:
	// ---- Geometry definition ----
	float radius;         // base radius
	float height;         // cone height
	uint32_t sectors;     // radial resolution

	// ---- Runtime state ----
	glm::vec3 position{0.0f, 0.0f, 0.1f};
	glm::vec3 color{ 1.0f, 0.0f, 0.0f };
	std::unique_ptr<Mesh> mesh;

	void BuildMesh();
};
