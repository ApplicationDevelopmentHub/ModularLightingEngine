#pragma once
#include<vector>
#include<cstdint>

class Mesh {
public:
	Mesh();
	~Mesh();

	void SetData(const std::vector<float>& vertices,
		const std::vector<uint32_t>& indices);

	void Draw() const;
private:
	unsigned int vao{ 0 }, vbo{ 0 }, ebo{ 0 };
	uint32_t indexCount{ 0 };
};
