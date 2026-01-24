#pragma once
#include"Renderer.h"
#include<memory>

class Shader;

class OpenGLRenderer :public Renderer {
public:
	OpenGLRenderer();

	void BeginFrame() override;
	void Render(const Scene& scene) override;
	void EndFrame() override;

	void BindMaterial() override;
private:
	std::unique_ptr<Shader> shader;
};