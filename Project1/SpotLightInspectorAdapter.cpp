#include "SpotLightInspectorAdapter.h"
#include <imgui.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpotLightInspectorAdapter::SpotLightInspectorAdapter(
    Scene& scene,
    LightHandle id)
    : scene(scene), id(id)
{
}

const char* SpotLightInspectorAdapter::GetLabel() const
{
    return "Spot Light";
}

void SpotLightInspectorAdapter::DrawInspectorUI()
{
    SpotLight* light = scene.GetSpotLight(id);
    if (!light)
        return;

    ImGui::TextUnformatted("Spot Light Properties");
    ImGui::Separator();

    // ----------------------------
    // Position
    // ----------------------------
    ImGui::DragFloat3(
        "Position",
        &light->position.x,
        0.05f);

    // ----------------------------
    // Direction
    // ----------------------------
    if (ImGui::DragFloat3(
        "Direction",
        &light->direction.x,
        0.01f))
    {
        light->direction = glm::normalize(light->direction);
    }

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
        50.0f);

    // ----------------------------
    // Range
    // ----------------------------
    ImGui::SliderFloat(
        "Range",
        &light->range,
        0.1f,
        200.0f);

    // ----------------------------
    // Cone Angles (convert from cosine to degrees for UI)
    // ----------------------------
    float innerDeg = glm::degrees(acos(light->innerCutoff));
    float outerDeg = glm::degrees(acos(light->outerCutoff));

    if (ImGui::SliderFloat(
        "Inner Angle",
        &innerDeg,
        1.0f,
        89.0f))
    {
        light->innerCutoff = glm::cos(glm::radians(innerDeg));
    }

    if (ImGui::SliderFloat(
        "Outer Angle",
        &outerDeg,
        1.0f,
        89.0f))
    {
        light->outerCutoff = glm::cos(glm::radians(outerDeg));
    }

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
