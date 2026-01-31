#include "Cone.h"
#include <vector>
#include <cmath>

Cone::Cone(float radius, float height, uint32_t sectors)
    : radius(radius),
    height(height),
    sectors(sectors),
    mesh(std::make_unique<Mesh>())
{
    BuildMesh();
}

const char* Cone::GetTypeName() const {
    return "Cone";
}

void Cone::Draw(Renderer& renderer) const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    renderer.SetMVP(model);
    renderer.SetColor(color);

    mesh->Draw();
}

// ---------------- Geometry accessors ----------------

float Cone::GetRadius() const {
    return radius;
}

void Cone::SetRadius(float radVal) {
    radius = radVal;
}

std::uint32_t Cone::GetHeight() const {
    return static_cast<std::uint32_t>(height);
}

void Cone::SetHeight(std::uint32_t h) {
    height = static_cast<float>(h);
}

std::uint32_t Cone::GetSectors() const {
    return sectors;
}

void Cone::SetSectors(std::uint32_t sector) {
    sectors = sector;
}

// ---------------- Visual ----------------

glm::vec3 Cone::GetColor() const {
    return color;
}

void Cone::SetColor(const glm::vec3& newColor) {
    color = newColor;
}

// ---------------- Transform ----------------

const glm::vec3& Cone::GetPosition() const {
    return position;
}

void Cone::SetPosition(const glm::vec3& p) {
    position = p;
}

// ---------------- Mesh rebuild ----------------

void Cone::RebuildMesh() {
    BuildMesh();
}

void Cone::BuildMesh()
{
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    const float step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);

    // Apex
    glm::vec3 apex(0.0f, height, 0.0f);

    // Generate ring vertices
    for (uint32_t i = 0; i <= sectors; ++i) {
        float angle = i * step;

        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        glm::vec3 pos(x, 0.0f, z);

        // Smooth side normal (PBR-friendly)
        glm::vec3 normal = glm::normalize(glm::vec3(x, radius / height, z));

        // Position
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);

        // Normal
        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);

        // UV (simple cylindrical mapping)
        vertices.push_back(static_cast<float>(i) / sectors);
        vertices.push_back(0.0f);
    }

    uint32_t apexIndex = static_cast<uint32_t>(vertices.size() / 8);

    // Apex vertex
    vertices.push_back(apex.x);
    vertices.push_back(apex.y);
    vertices.push_back(apex.z);

    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);

    vertices.push_back(0.5f);
    vertices.push_back(1.0f);

    // Indices (side faces only)
    for (uint32_t i = 0; i < sectors; ++i) {
        indices.push_back(apexIndex);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh->SetData(vertices, indices);
}
