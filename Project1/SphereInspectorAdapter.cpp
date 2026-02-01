#include "SphereInspectorAdapter.h"
#include <imgui.h>

SphereInspectorAdapter::SphereInspectorAdapter(Sphere& sphere, PrimitiveHandle id)
    : sphere(sphere),id(id) {
}

const char* SphereInspectorAdapter::GetLabel() const {
    return "Sphere";
}

void SphereInspectorAdapter::DrawInspectorUI()
{
    // -------- Position (cheap, transform-only) --------
    glm::vec3 pos = sphere.GetPosition();
    if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) {
        sphere.SetPosition(pos);
    }

    ImGui::Separator();

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

    ImGui::Separator();

    // -------- Material (PBR) --------
    Material& mat = *sphere.GetMaterial();

    ImGui::Separator();
    ImGui::TextUnformatted("PBR Material Properties");
    ImGui::Separator();


    // -------- Albedo --------
    glm::vec3 albedo = mat.GetAlbedo();
    if (ImGui::ColorEdit3("Albedo", &albedo.x)) {
        mat.SetAlbedo(albedo);
    }

    // -------- Roughness --------
    float roughness = mat.GetRoughness();
    if (ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f)) {
        mat.SetRoughness(roughness);
    }

    // -------- Metallic --------
    float metallic = mat.GetMetallic();
    if (ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f)) {
        mat.SetMetallic(metallic);
    }

    // -------- Ambient Occlusion --------
    float ao = mat.GetAO();
    if (ImGui::SliderFloat("AO", &ao, 0.0f, 1.0f)) {
        mat.SetAO(ao);
    }

    ImGui::Separator();

    // -------- Color (cheap, visual-only) --------
    //glm::vec3 color = sphere.GetColor();
    //if (ImGui::ColorEdit3("Color", &color.x)) {
    //    sphere.SetColor(color); // instant visual update
    //}

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.1725f, 0.2824f, 0.6588f, 1.0f });
    if (ImGui::Button("Delete Sphere")) {
        deleteRequested = true;
    }
    ImGui::PopStyleColor();
}

bool SphereInspectorAdapter::HasPendingChanges() const {
    return false;
}

void SphereInspectorAdapter::ApplyChanges() {
    // live editing → nothing to apply
}

bool SphereInspectorAdapter::WantsDelete() const {
    return deleteRequested;
}
