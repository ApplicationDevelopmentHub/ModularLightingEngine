#include "SphereInspectorAdapter.h"
#include <imgui.h>

SphereInspectorAdapter::SphereInspectorAdapter(Sphere& sphere)
    : sphere(sphere) {
}

const char* SphereInspectorAdapter::GetLabel() const {
    return "Sphere";
}

void SphereInspectorAdapter::DrawInspectorUI()
{
    // -------- Radius (geometry-affecting) --------
    float radius = sphere.GetRadius();
    if (ImGui::DragFloat(
        "Radius",
        &radius,
        0.05f,
        0.01f,
        100.0f))
    {
        sphere.SetRadius(radius);
        sphere.RebuildMesh();   // expensive → rebuild only when changed
    }

    // -------- Stacks (geometry-affecting) --------
    int stacks = static_cast<int>(sphere.GetStack());
    if (ImGui::DragInt(
        "Stacks",
        &stacks,
        1,
        2,
        256))
    {
        sphere.SetStack(static_cast<uint32_t>(stacks));
        sphere.RebuildMesh();
    }

    // -------- Sectors (geometry-affecting) --------
    int sectors = static_cast<int>(sphere.GetSectors());
    if (ImGui::DragInt(
        "Sectors",
        &sectors,
        1,
        3,
        256))
    {
        sphere.SetSectors(static_cast<uint32_t>(sectors));
        sphere.RebuildMesh();
    }

    // -------- Color (cheap, visual-only) --------
    glm::vec3 color = sphere.GetColor();
    if (ImGui::ColorEdit3("Color", &color.x)) {
        sphere.SetColor(color); // instant visual update
    }
}

bool SphereInspectorAdapter::HasPendingChanges() const {
    return false;
}

void SphereInspectorAdapter::ApplyChanges() {
    // live editing → nothing to apply
}
