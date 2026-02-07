#pragma once
#include"Renderer.h"
#include<memory>
#include"Camera.h"
#include<glm/glm.hpp>
#include<cstdint>
#include<GL/glew.h>
class Shader;

class OpenGLRenderer :public Renderer {
public:
	OpenGLRenderer();

	void BeginFrame() override;
	void Render(const Scene& scene, const Camera& cam) override;
	void EndFrame() override;

	void SetMVP(const glm::mat4& model) override;
	void SetColor(const glm::vec3& col) override;

	void ApplyMaterial(const Material& material) override;
private:
	std::unique_ptr<Shader> shader;
	const Camera* camera = nullptr;

	static constexpr uint32_t MAX_DIR_LIGHTS = 16;

	GLuint lightUBO = 0;
};