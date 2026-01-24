#include"Mesh.h"
#include<GL/glew.h>

Mesh::Mesh() {
	glGenVertexArrays(1, &vao); //generates 1 VAO object, stores ID in vao (RECIEPE)
	glGenBuffers(1, &vbo); //generates 1 VBO object and stores id in vbo 
	glGenBuffers(1, &ebo); //generates 1 ebo object and stores id in ebo (INDICES, REDUNDANCY)
}

Mesh::~Mesh() {
	//Resource cleanup: free memory in GPU
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::SetData(const std::vector<float>& vertices,
	const std::vector<uint32_t>& indices) {

	indexCount = static_cast<uint32_t>(indices.size());

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(float),
		vertices.data(),
		GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(uint32_t),
		indices.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void Mesh::Draw() const {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES,indexCount,GL_UNSIGNED_INT,nullptr);
}