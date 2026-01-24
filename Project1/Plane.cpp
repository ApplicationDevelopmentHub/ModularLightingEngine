#include"Plane.h"
#include<vector>

Plane::Plane(float size):mesh(std::make_unique<Mesh>()) {
	//layout: pos, normal, uv
	std::vector<float> vertices = {
		-size,0,-size,0,1,0,0,0,
		size,0,-size,0,1,0,1,0,
		size,0,size,0,1,0,1,1,
		-size,0,size,0,1,0,0,1
	};

	//indices of order of drawing triangles
	std::vector<uint32_t> indices = {
		0,1,2,
		2,3,0
	};

	mesh->SetData(vertices,indices);
}

void Plane::Draw(Renderer& renderer) const {
	renderer.BindMaterial();
	mesh->Draw();
}
