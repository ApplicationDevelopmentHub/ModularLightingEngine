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

	//Shape modification
	std::uint32_t GetStack() const;
	void SetStack(std::uint32_t stack);

	std::uint32_t GetSectors() const;
	void SetSectors(std::uint32_t sector);

	float GetRadius() const;
	void SetRadius(float radVal);

	glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& newColor);

	void RebuildMesh();
private:
	std::uint32_t stacks;
	std::uint32_t sectors;
	float radius;
	glm::vec3 color{ 0.0549f, 0.4353f, 0.4235f };
	std::unique_ptr<Mesh> mesh;

	void BuildMesh();
};