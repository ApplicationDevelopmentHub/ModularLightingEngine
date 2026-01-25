#pragma once
#include"Renderer.h"
#include<memory>
#include"Camera.h"
#include<glm/glm.hpp>

class Shader;

class OpenGLRenderer :public Renderer {
public:
	OpenGLRenderer();

	void BeginFrame() override;
	void Render(const Scene& scene, const Camera& cam) override;
	void EndFrame() override;

	Camera& GetCamera();

	void SetMVP(const glm::mat4& model);
private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Camera> camera;
};