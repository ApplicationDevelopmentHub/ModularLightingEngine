#include "BoxInspectorAdapter.h"
#include <imgui.h>

BoxInspectorAdapter::BoxInspectorAdapter(Box& box, PrimitiveHandle id)
    : box(box),id(id) {
}

const char* BoxInspectorAdapter::GetLabel() const {
    return "Box";
}

void BoxInspectorAdapter::DrawInspectorUI()
{
    // -------- Position (cheap, transform-only) --------
    glm::vec3 pos = box.GetPosition();
    if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) {
        box.SetPosition(pos);
    }

    ImGui::Separator();

    // -------- Geometry (expensive → rebuild) --------
    float width = box.GetWidth();
    float height = box.GetHeight();
    float length = box.GetLength();

    bool geometryChanged = false;

    geometryChanged |= ImGui::DragFloat(
        "Width",
        &width,
        0.05f,
        0.01f,
        100.0f
    );

    geometryChanged |= ImGui::DragFloat(
        "Height",
        &height,
        0.05f,
        0.01f,
        100.0f
    );

    geometryChanged |= ImGui::DragFloat(
        "Length",
        &length,
        0.05f,
        0.01f,
        100.0f
    );

    if (geometryChanged) {
        box.SetWidth(width);
        box.SetHeight(height);
        box.SetLength(length);
        box.RebuildMesh();
    }

    ImGui::Separator();

    // -------- Material (PBR) --------
    Material& mat = *box.GetMaterial();

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
   /* glm::vec3 color = box.GetColor();
    if (ImGui::ColorEdit3("Color", &color.x)) {
        box.SetColor(color);
    }*/

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.1725f, 0.2824f, 0.6588f, 1.0f });
    if (ImGui::Button("Delete Box")) {
        deleteRequested = true;
    }
    ImGui::PopStyleColor();
}


bool BoxInspectorAdapter::HasPendingChanges() const {
    return false;
}

void BoxInspectorAdapter::ApplyChanges() {
    // live editing → nothing to apply
}

bool BoxInspectorAdapter::WantsDelete() const {
    return deleteRequested;
}
