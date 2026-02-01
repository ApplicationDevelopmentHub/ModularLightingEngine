#include"Plane.h"
#include<vector>
#include<iostream>

Plane::Plane(float size):mesh(std::make_unique<Mesh>()),size(size) {
	std::cout << "Plane constructor." << std::endl;

	//layout: pos(3), normal(3), uv(3)
	std::vector<float> vertices = {
		-size,0,-size, 0,1,0, 0,0, //0,0 of texture coordinates lies on this vertex
		size,0,-size, 0,1,0, 1,0,
		size,0,size, 0,1,0, 1,1,
		-size,0,size, 0,1,0 ,0,1
	};

	//indices of order of drawing triangles
	std::vector<uint32_t> indices = {
		0,1,2,
		2,3,0
	};

	mesh->SetData(vertices,indices);
}

void Plane::Draw(Renderer& renderer) const {
	glm::mat4 model = glm::mat4(1.0f);

	renderer.SetMVP(model);

	//Do not assign hard coded value
	//Draw function is being called every frame, so the value overrides
	//For inspector based changes, 'color' must be mentioned not vec3 0.8
	//renderer.SetColor(color);
	renderer.ApplyMaterial(*GetMaterial());

	mesh->Draw();
}

const char* Plane::GetTypeName() const { return "Plane"; }

//Plane modification

float Plane::GetSize() const {
	return size;
}

void Plane::SetSize(float newSize) {
	size = newSize;
}

glm::vec3 Plane::GetColor() const {
	return color;
}

void Plane::SetColor(const glm::vec3& newColor) {
	color = newColor;
}

void Plane::RebuildMesh() {
	BuildMesh();
}

void Plane::BuildMesh() {
	std::vector<float> vertices = {
		-size,0,-size, 0,1,0, 0,0,
		 size,0,-size, 0,1,0, 1,0,
		 size,0, size, 0,1,0, 1,1,
		-size,0, size, 0,1,0, 0,1
	};

	std::vector<uint32_t> indices = {
		0,1,2,
		2,3,0
	};

	mesh->SetData(vertices, indices);
}
