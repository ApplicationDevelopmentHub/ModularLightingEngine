#pragma once
#include"Primitive.h"
#include"Mesh.h"
#include<memory>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Material.h"

class Box :public Primitive {
public:
	explicit Box(float length, float width, float height);

	const char* GetTypeName() const override;
	void Draw(Renderer& renderer) const override;

	//Modification functions
	float GetLength() const;
	void SetLength(float l);

	float GetWidth() const;
	void SetWidth(float w);

	float GetHeight() const;
	void SetHeight(float h);

	glm::vec3 GetColor() const;
	void SetColor(glm::vec3 col);

	const glm::vec3& GetPosition() const;
	void SetPosition(glm::vec3 pos);

	void RebuildMesh();

private:
	float length;
	float width;
	float height;

	glm::vec3 position { 0.0f,1.0f,0.0f };
	glm::vec3 color { 0.0549f, 0.4353f, 0.4235f };

	std::unique_ptr<Mesh> mesh;

	void BuildMesh();

	std::shared_ptr<Material> material;
};
