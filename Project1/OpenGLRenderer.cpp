#include "OpenGLRenderer.h"
#include "Scene.h"
#include "Primitive.h"
#include"Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//What shader to use? Fetch using path
//Path fetching is defined in Shader program
OpenGLRenderer::OpenGLRenderer() {
	shader = std::make_unique<Shader>(
		"basic.vert",
		"basic.frag"
	);
}

void OpenGLRenderer::BeginFrame() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Render(
    const Scene& scene,
    const Camera& cam
) {
    camera = &cam;
    for (const auto& [id, primitive] : scene.GetPrimitives()) {

        shader->Bind();

        /*glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 mvp =
            camera.GetProjection() *
            camera.GetView() *
            model;

        shader->SetMat4("uMVP", mvp);
        shader->SetVec3("uColor", glm::vec3(0.8f));*/

        primitive->Draw(*this);
    }
}

void OpenGLRenderer::EndFrame() {
	// nothing yet
}

void OpenGLRenderer::SetMVP(const glm::mat4& model) {
    shader->Bind();

    glm::mat4 mvp =
        camera->GetProjection() *
        camera->GetView() *
        model;

    shader->SetMat4("uMVP", mvp);
    //shader->SetVec3("uColor", glm::vec3(0.8f));
}

void OpenGLRenderer::SetColor(const glm::vec3& color) {
    // Assumes shader is already bound
    shader->SetVec3("uColor", color);
}
