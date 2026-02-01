#include "DirectionalLightInspectorAdapter.h"
#include <imgui.h>

DirectionalLightInspectorAdapter::DirectionalLightInspectorAdapter(
    Scene& scene,
    LightHandle id)
    : scene(scene), id(id) {
}

const char* DirectionalLightInspectorAdapter::GetLabel() const {
    return "Directional Light";
}

void DirectionalLightInspectorAdapter::DrawInspectorUI()
{
    DirectionalLight* light = scene.GetDirectionalLight(id);

    ImGui::TextUnformatted("Light Properties");
    ImGui::Separator();

    ImGui::DragFloat3(
        "Direction",
        &light->direction.x,
        0.01f);

    ImGui::ColorEdit3(
        "Color",
        &light->color.x);

    ImGui::SliderFloat(
        "Intensity",
        &light->intensity,
        0.0f,
        20.0f);

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Button,
        { 0.8f, 0.2f, 0.2f, 1.0f });

    if (ImGui::Button("Delete Light")) {
        deleteRequested = true;
    }

    ImGui::PopStyleColor();
}
