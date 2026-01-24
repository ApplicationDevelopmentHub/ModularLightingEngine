#include "OpenGLRenderer.h"
#include "Scene.h"
#include "Primitive.h"
#include"Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//class Shader;

OpenGLRenderer::OpenGLRenderer() {
	shader = std::make_unique<Shader>(
		"shaders/basic.vert",
		"shaders/basic.frag"
	);
}

void OpenGLRenderer::BeginFrame() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::BindMaterial() {
	shader->Bind();

	// TEMP: identity MVP (camera comes next)
	//glm::mat4 mvp(1.0f);
	glm::mat4 mvp =
		glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	shader->SetMat4("uMVP", mvp);
	shader->SetVec3("uColor", glm::vec3(0.8f));
}

void OpenGLRenderer::Render(const Scene& scene) {
	for (const auto& [id, primitive] : scene.GetPrimitives()) {
		primitive->Draw(*this);
	}
}

void OpenGLRenderer::EndFrame() {
	// nothing yet
}
