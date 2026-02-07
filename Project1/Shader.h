#pragma once
#include<glm/glm.hpp>
#include<string>
#include<iostream>
#include<vector>

class Shader {
public:
	explicit Shader(const std::string& vertexPath,
		const std::string& fragmentPath);
	~Shader();

	void Bind() const;

	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);

private:
	unsigned program;

	std::string LoadFile(const std::string& path);
	unsigned Compile(unsigned type, const std::string& source);
};
