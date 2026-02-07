#include "OpenGLRenderer.h"
#include "Scene.h"
#include "Primitive.h"
#include"Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//OpenGL Renderer constructor
//What shader to use? Fetch using path
//Path fetching is defined in Shader program
OpenGLRenderer::OpenGLRenderer()
{
    shader = std::make_unique<Shader>(
        "pbr.vert",
        "pbr2.frag"
    );

    // ------------------------------------------------
    // Validate shader program
    // ------------------------------------------------
    if (!shader || shader->GetProgram() == 0)
    {
        std::cerr << "Shader program invalid in OpenGLRenderer!\n";
        return;
    }

    // ------------------------------------------------
    // Create UBO
    // ------------------------------------------------
    glGenBuffers(1, &lightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);

    // Calculate required block size (std140 layout)
    size_t blockSize =
        sizeof(int) * 4 +                                   // 4 ints (aligned to 16 bytes)
        sizeof(glm::vec4) * MAX_DIR_LIGHTS * 2 +            // dir directions + dir colors
        sizeof(glm::vec4) * MAX_SPOT_LIGHTS * 4;            // spot pos + dir + color + params

    // ------------------------------------------------
    // Safety: Check against hardware limit
    // ------------------------------------------------
    GLint maxBlockSize = 0;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxBlockSize);

    if (blockSize > static_cast<size_t>(maxBlockSize))
    {
        std::cerr << "Light UBO exceeds GL_MAX_UNIFORM_BLOCK_SIZE!\n";
        std::cerr << "Requested: " << blockSize
            << "  Max: " << maxBlockSize << "\n";
    }

    glBufferData(GL_UNIFORM_BUFFER, blockSize, nullptr, GL_DYNAMIC_DRAW);

    // ------------------------------------------------
    // Bind UBO to binding point 0
    // ------------------------------------------------
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);

    // ------------------------------------------------
    // Link shader block to binding point 0
    // ------------------------------------------------
    GLuint blockIndex =
        glGetUniformBlockIndex(shader->GetProgram(), "LightBlock");

    if (blockIndex == GL_INVALID_INDEX)
    {
        std::cerr << "LightBlock not found in shader!\n";
    }
    else
    {
        glUniformBlockBinding(shader->GetProgram(), blockIndex, 0);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void OpenGLRenderer::BeginFrame() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::Render(const Scene& scene, const Camera& cam)
{
    camera = &cam;

    // ------------------------------------------------
    // 1️⃣ Upload UBO once per frame
    // ------------------------------------------------
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);

    struct LightBlockCPU
    {
        int dirCount;
        int pointCount;
        int spotCount;
        float pad0;

        glm::vec4 dirDirections[MAX_DIR_LIGHTS];
        glm::vec4 dirColors[MAX_DIR_LIGHTS];

        glm::vec4 spotPositions[MAX_SPOT_LIGHTS];
        glm::vec4 spotDirections[MAX_SPOT_LIGHTS];
        glm::vec4 spotColors[MAX_SPOT_LIGHTS];
        glm::vec4 spotParams[MAX_SPOT_LIGHTS];
    };

    LightBlockCPU block{};
    block.dirCount = 0;

    for (const auto& [id, light] : scene.GetDirectionalLights())
    {
        if (!light.enabled) continue;
        if (block.dirCount >= MAX_DIR_LIGHTS) break;

        block.dirDirections[block.dirCount] =
            glm::vec4(glm::normalize(light.direction), 0.0f);

        block.dirColors[block.dirCount] =
            glm::vec4(light.color * light.intensity, 0.0f);

        block.dirCount++;
    }

    block.spotCount = 0;

    for (const auto& [id, light] : scene.GetSpotLights())
    {
        if (!light.enabled) continue;
        if (block.spotCount >= MAX_SPOT_LIGHTS) break;

        int i = block.spotCount;

        block.spotPositions[i] =
            glm::vec4(light.position, 0.0f);

        block.spotDirections[i] =
            glm::vec4(glm::normalize(light.direction), 0.0f);

        block.spotColors[i] =
            glm::vec4(light.color * light.intensity, 0.0f);

        block.spotParams[i] =
            glm::vec4(
                light.innerCutoff,
                light.outerCutoff,
                light.range,
                0.0f
            );

        block.spotCount++;
    }


    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightBlockCPU), &block);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // ------------------------------------------------
    // 2️⃣ Bind shader ONCE
    // ------------------------------------------------
    shader->Bind();
    shader->SetVec3("uCamPos", camera->GetPosition());

    // ------------------------------------------------
    // 3️⃣ Draw primitives ONCE
    // ------------------------------------------------
    for (const auto& [id, primitive] : scene.GetPrimitives())
    {
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

