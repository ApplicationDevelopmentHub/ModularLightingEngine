#include "Box.h"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Box::Box(float l, float w, float h)
    : mesh(std::make_unique<Mesh>()),
    length(l),
    width(w),
    height(h) {

    std::cout << "Box constructor." << std::endl;

    float hx = l * 0.5f;
    float hy = h * 0.5f;
    float hz = w * 0.5f;

    std::vector<float> vertices = {

        // ---------- FRONT (+Z) ----------
        -hx, -hy,  hz,   0, 0, 1,   0, 0,
         hx, -hy,  hz,   0, 0, 1,   1, 0,
         hx,  hy,  hz,   0, 0, 1,   1, 1,
        -hx,  hy,  hz,   0, 0, 1,   0, 1,

        // ---------- BACK (-Z) ----------
         hx, -hy, -hz,   0, 0,-1,   0, 0,
        -hx, -hy, -hz,   0, 0,-1,   1, 0,
        -hx,  hy, -hz,   0, 0,-1,   1, 1,
         hx,  hy, -hz,   0, 0,-1,   0, 1,

         // ---------- RIGHT (+X) ----------
          hx, -hy,  hz,   1, 0, 0,   0, 0,
          hx, -hy, -hz,   1, 0, 0,   1, 0,
          hx,  hy, -hz,   1, 0, 0,   1, 1,
          hx,  hy,  hz,   1, 0, 0,   0, 1,

          // ---------- LEFT (-X) ----------
          -hx, -hy, -hz,  -1, 0, 0,   0, 0,
          -hx, -hy,  hz,  -1, 0, 0,   1, 0,
          -hx,  hy,  hz,  -1, 0, 0,   1, 1,
          -hx,  hy, -hz,  -1, 0, 0,   0, 1,

          // ---------- TOP (+Y) ----------
          -hx,  hy,  hz,   0, 1, 0,   0, 0,
           hx,  hy,  hz,   0, 1, 0,   1, 0,
           hx,  hy, -hz,   0, 1, 0,   1, 1,
          -hx,  hy, -hz,   0, 1, 0,   0, 1,

          // ---------- BOTTOM (-Y) ----------
          -hx, -hy, -hz,   0,-1, 0,   0, 0,
           hx, -hy, -hz,   0,-1, 0,   1, 0,
           hx, -hy,  hz,   0,-1, 0,   1, 1,
          -hx, -hy,  hz,   0,-1, 0,   0, 1
    };

    std::vector<uint32_t> indices;
    indices.reserve(36);

    for (uint32_t i = 0; i < 6; ++i) {
        uint32_t base = i * 4;
        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);
        indices.push_back(base + 2);
        indices.push_back(base + 3);
        indices.push_back(base + 0);
    }

    mesh->SetData(vertices, indices);
}

void Box::Draw(Renderer& renderer) const {
    // Place box on top of plane (plane at y = 0)
    glm::mat4 model = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f, height * 0.5f, 0.0f)
    );

    renderer.SetMVP(model);
    renderer.SetColor(glm::vec3(0.71f, 0.64f, 0.42f)); // neutral box color

    mesh->Draw();
}

const char* Box::GetTypeName() const {
    return "Box";
}
