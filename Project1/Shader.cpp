#include"Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::LoadFile(const std::string& path) {
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

unsigned Shader::Compile(unsigned type, const std::string& src) {
	std::cout << "Compiling the shader: " << type << std::endl;

	unsigned id = glCreateShader(type);
	const char* s = src.c_str();
	glShaderSource(id, 1, &s, nullptr); //links program extracted in string to shader object
	glCompileShader(id);

	//Checking if the shader compilation failed or succes
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info[512];
		glGetShaderInfoLog(id, 512, nullptr, info);
		std::cerr << "Shader compile error:\n" << info << std::endl;
	}

	return id;
}

//called in the opengl renderer constructor
Shader::Shader(const std::string& vertPath,
	const std::string& fragPath) {

	//store shader programs from disk file in a string 
	std::string vertSrc = LoadFile(vertPath); 
	std::string fragSrc = LoadFile(fragPath);

	unsigned vs = Compile(GL_VERTEX_SHADER, vertSrc);
	unsigned fs = Compile(GL_FRAGMENT_SHADER, fragSrc);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	//OpenGL matches in and out during stages
	//Resolves uniforms and validates types
	//Generates final GPU machine code or driver IR.
	glLinkProgram(program);

	//Check if the link was success
	GLint success;
	glGetProgramiv(program,GL_LINK_STATUS,&success); //store the link status in success
	if (!success) {
		GLint logLength = 0;
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&logLength); //store the info length in log length
		std::vector<char> infoLog(logLength);
		glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());

		std::cerr << "Shader Program Linking Failed:\n"
			<< infoLog.data() << std::endl;
	}
	else {
		std::cout << "Shader program link success." << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader() {
	glDeleteProgram(program);
}

//Use this generated shader program for rendering
void Shader::Bind() const {
	glUseProgram(program);
}

void Shader::SetInt(const std::string& name, int v) {
	glUniform1i(glGetUniformLocation(program, name.c_str()), v);
}

void Shader::SetFloat(const std::string& name, float v) {
	glUniform1f(glGetUniformLocation(program, name.c_str()), v);
}

//finds uniform in the compiled shader program , not in shader code
void Shader::SetVec3(const std::string& name, const glm::vec3& v) {
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &v[0]);

	//ADVANCED VERSION FOR DEFEINSIVE AND DEBUG SAFE
	/*GLint loc = glGetUniformLocation(program, name.c_str());
	if (loc == -1) {
		std::cerr << "Uniform not found or optimized out: " << name << std::endl;
		return;
	}
	glUniform3fv(loc, 1, &v[0]);*/
}

void Shader::SetMat4(const std::string& name, const glm::mat4& m) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()),
		1, GL_FALSE, &m[0][0]);
}
