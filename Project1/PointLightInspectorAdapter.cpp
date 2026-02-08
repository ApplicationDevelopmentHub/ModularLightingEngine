#include "PointLightInspectorAdapter.h"
#include <imgui.h>
#include <glm/glm.hpp>

PointLightInspectorAdapter::PointLightInspectorAdapter(
    Scene& scene,
    LightHandle id)
    : scene(scene), id(id)
{
}

const char* PointLightInspectorAdapter::GetLabel() const
{
    return "Point Light";
}

void PointLightInspectorAdapter::DrawInspectorUI()
{
    PointLight* light = scene.GetPointLight(id);
    if (!light)
        return;

    ImGui::TextUnformatted("Point Light Properties");
    ImGui::Separator();

    // ----------------------------
    // Position
    // ----------------------------
    ImGui::DragFloat3(
        "Position",
        &light->position.x,
        0.05f);

    // ----------------------------
    // Color
    // ----------------------------
    ImGui::ColorEdit3(
        "Color",
        &light->color.x);

    // ----------------------------
    // Intensity
    // ----------------------------
    ImGui::SliderFloat(
        "Intensity",
        &light->intensity,
        0.0f,
        100.0f);

    // ----------------------------
    // Range
    // ----------------------------
    ImGui::SliderFloat(
        "Range",
        &light->range,
        0.1f,
        200.0f);

    // ----------------------------
    // Radius (affects specular highlight size in PBR)
    // ----------------------------
    ImGui::SliderFloat(
        "Emitter Radius",
        &light->radius,
        0.0f,
        5.0f);

    // ----------------------------
    // Enable / Disable
    // ----------------------------
    ImGui::Checkbox(
        "Enabled",
        &light->enabled);

    ImGui::Separator();

    ImGui::PushStyleColor(
        ImGuiCol_Button,
        { 0.8f, 0.2f, 0.2f, 1.0f });

    if (ImGui::Button("Delete Light"))
    {
        deleteRequested = true;
    }

    ImGui::PopStyleColor();
}
