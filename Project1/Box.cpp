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
        position
    );

    renderer.SetMVP(model);
    renderer.SetColor(color); // neutral box color

    mesh->Draw();
}

const char* Box::GetTypeName() const {
    return "Box";
}

//Modifications based functions
float Box::GetLength() const {
    return length;
}
void Box::SetLength(float l) {
    length = l;
}

float Box::GetWidth() const {
    return width;
}

void Box::SetWidth(float w) {
    width = w;
}

float Box::GetHeight() const {
    return height;
}

void Box::SetHeight(float h) {
    height = h;
}

const glm::vec3& Box::GetPosition() const {
    return position;
}

void Box::SetPosition(const glm::vec3 pos) {
    position = pos;
}

glm::vec3 Box::GetColor() const {
    return color;
}
void Box::SetColor(glm::vec3 col) {
    color = col;
}


void Box::BuildMesh() {
    float hx = length * 0.5f;
    float hy = height * 0.5f;
    float hz = width * 0.5f;

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

void Box::RebuildMesh() {
    BuildMesh();
}
