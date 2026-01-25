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

//Camera pending: workarounf
//void OpenGLRenderer::BindMaterial() {
//	shader->Bind();
//
//    glm::mat4 model =
//        glm::rotate(glm::mat4(1.0f),
//            glm::radians(-90.0f),
//            glm::vec3(1.0f, 0.0f, 0.0f));
//
//    // -------- VIEW (static observer) --------
//    glm::mat4 view = glm::lookAt(
//        glm::vec3(0.0f, 3.0f, 6.0f),
//        glm::vec3(0.0f, 0.0f, 0.0f),
//        glm::vec3(0.0f, 1.0f, 0.0f)
//    );
//
//    // -------- PROJECTION --------
//    glm::mat4 projection = glm::perspective(
//        glm::radians(45.0f),
//        1920.0f / 1080.0f,
//        0.1f,
//        100.0f
//    );
//
//    glm::mat4 mvp = projection * view * model;
//	shader->SetMat4("uMVP", mvp);
//	shader->SetVec3("uColor", glm::vec3(0.8f));
//}
//
//void OpenGLRenderer::Render(const Scene& scene,const Camera& cam) {
//	for (const auto& [id, primitive] : scene.GetPrimitives()) {
//        SetMVP(glm::mat4(1.0f));
//		primitive->Draw(*this);
//	}
//}

void OpenGLRenderer::Render(
    const Scene& scene,
    const Camera& camera
) {
    for (const auto& [id, primitive] : scene.GetPrimitives()) {

        shader->Bind();

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 mvp =
            camera.GetProjection() *
            camera.GetView() *
            model;

        shader->SetMat4("uMVP", mvp);
        shader->SetVec3("uColor", glm::vec3(0.8f));

        primitive->Draw(*this);
    }
}

void OpenGLRenderer::EndFrame() {
	// nothing yet
}

Camera& OpenGLRenderer::GetCamera() {
    return *camera;
}

void OpenGLRenderer::SetMVP(const glm::mat4& model) {
    shader->Bind();

    glm::mat4 mvp =
        camera->GetProjection() *
        camera->GetView() *
        model;

    shader->SetMat4("uMVP", mvp);
    shader->SetVec3("uColor", glm::vec3(0.8f));
}
