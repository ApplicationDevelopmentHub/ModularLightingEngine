#include "ConeInspectorAdapter.h"
#include <imgui.h>

ConeInspectorAdapter::ConeInspectorAdapter(Cone& cone, PrimitiveHandle id)
    : cone(cone),id(id) {
}

const char* ConeInspectorAdapter::GetLabel() const {
    return "Cone";
}

void ConeInspectorAdapter::DrawInspectorUI()
{
    // ---------- Transform ----------
    glm::vec3 position = cone.GetPosition();
    if (ImGui::DragFloat3("Position", &position.x, 0.1f)) {
        cone.SetPosition(position);
    }

    ImGui::Separator();

    // ---------- Radius (geometry-affecting) ----------
    float radius = cone.GetRadius();
    if (ImGui::DragFloat(
        "Radius",
        &radius,
        0.05f,
        0.01f,
        100.0f))
    {
        cone.SetRadius(radius);
        cone.RebuildMesh();
    }

    // ---------- Height (geometry-affecting) ----------
    float height = static_cast<float>(cone.GetHeight());
    if (ImGui::DragFloat(
        "Height",
        &height,
        0.05f,
        0.01f,
        100.0f))
    {
        cone.SetHeight(static_cast<std::uint32_t>(height));
        cone.RebuildMesh();
    }

    // ---------- Sectors (geometry-affecting) ----------
    int sectors = static_cast<int>(cone.GetSectors());
    if (ImGui::DragInt(
        "Sectors",
        &sectors,
        1,
        3,
        256))
    {
        cone.SetSectors(static_cast<uint32_t>(sectors));
        cone.RebuildMesh();
    }

    ImGui::Separator();

    ImGui::Separator();

    // -------- Material (PBR) --------
    Material& mat = *cone.GetMaterial();

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

    //// ---------- Color (cheap, visual-only) ----------
    //glm::vec3 color = cone.GetColor();
    //if (ImGui::ColorEdit3("Color", &color.x)) {
    //    cone.SetColor(color);
    //}

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.1725f, 0.2824f, 0.6588f, 1.0f });
    if (ImGui::Button("Delete Cone")) {
        deleteRequested = true;
    }
    ImGui::PopStyleColor();
}


bool ConeInspectorAdapter::HasPendingChanges() const {
    return false; // live editing
}

void ConeInspectorAdapter::ApplyChanges() {
    // No-op: changes are applied immediately
}

bool ConeInspectorAdapter::WantsDelete() const {
    return deleteRequested;
}
