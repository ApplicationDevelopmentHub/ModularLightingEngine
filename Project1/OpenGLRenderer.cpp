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
		"pbr.vert",
		"pbr.frag"
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

        /*shader->Bind();
        primitive->Draw(*this);*/

        //NEW
        camera = &cam;

        shader->Bind();

        // 1️⃣ Camera (needed for specular)
        shader->SetVec3("uCamPos", camera->GetPosition());

        // 2️⃣ Directional light (THIS BLOCK GOES HERE)
        bool lightBound = false;
        for (const auto& [id, light] : scene.GetDirectionalLights())
        {
            if (!light.enabled) continue;

            shader->SetVec3("uLightDir", light.direction);
            shader->SetVec3("uLightColor", light.color * light.intensity);
            lightBound = true;
            break;
        }

        if (!lightBound)
        {
            shader->SetVec3("uLightColor", glm::vec3(0.0f));
        }

        // 3️⃣ Draw primitives
        for (const auto& [id, primitive] : scene.GetPrimitives())
        {
            primitive->Draw(*this);
        }
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
    shader->SetMat4("uModel", model);
    //shader->SetVec3("uColor", glm::vec3(0.8f));
}

void OpenGLRenderer::SetColor(const glm::vec3& color) {
    // Assumes shader is already bound
    shader->Bind();
    shader->SetVec3("uColor", color);
}

void OpenGLRenderer::ApplyMaterial(const Material& material)
{
    shader->Bind();

    shader->SetInt("uShadingModel",
        static_cast<int>(material.GetShadingModel()));

    shader->SetVec3("uAlbedo", material.GetAlbedo());
    shader->SetFloat("uMetallic", material.GetMetallic());
    shader->SetFloat("uRoughness", material.GetRoughness());
    shader->SetFloat("uAO", material.GetAO());
}

