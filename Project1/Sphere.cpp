#include "Sphere.h"
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // glm::pi

Sphere::Sphere(float radius, uint32_t stacks, uint32_t sectors)
    : mesh(std::make_unique<Mesh>()) {

    std::cout << "Sphere constructor." << std::endl;

    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    const float pi = glm::pi<float>();

    for (uint32_t i = 0; i <= stacks; ++i) {
        float v = static_cast<float>(i) / stacks;
        float phi = v * pi; // 0  PI

        for (uint32_t j = 0; j <= sectors; ++j) {
            float u = static_cast<float>(j) / sectors;
            float theta = u * 2.0f * pi; // 0  2PI

            // Unit sphere position
            glm::vec3 pos;
            pos.x = glm::sin(phi) * glm::cos(theta);
            pos.y = glm::cos(phi);
            pos.z = glm::sin(phi) * glm::sin(theta);

            glm::vec3 normal = glm::normalize(pos);
            glm::vec3 position = pos * radius;

            // Position
            vertices.push_back(position.x);
            vertices.push_back(position.y);
            vertices.push_back(position.z);

            // Normal
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);

            // UV
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // Indices
    for (uint32_t i = 0; i < stacks; ++i) {
        uint32_t k1 = i * (sectors + 1);
        uint32_t k2 = k1 + sectors + 1;

        for (uint32_t j = 0; j < sectors; ++j, ++k1, ++k2) {

            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    mesh->SetData(vertices, indices);
}

void Sphere::Draw(Renderer& renderer) const {
    glm::mat4 model = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)  // y = 0.5
    );

    renderer.SetMVP(model);
    renderer.SetColor(glm::vec3(0.0f, 0.0f, 0.5f)); // cyan

    mesh->Draw();
}
