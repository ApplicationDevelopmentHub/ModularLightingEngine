#include "PlaneInspectorAdapter.h"
#include <imgui.h>

//PlaneInspectorAdapter::PlaneInspectorAdapter(Plane& plane)
//    : plane(plane),
//    editSize(plane.GetSize()),
//    editColor(plane.GetColor()) {
//}

PlaneInspectorAdapter::PlaneInspectorAdapter(Plane& plane, PrimitiveHandle id)
    : plane(plane),id(id) {
}

const char* PlaneInspectorAdapter::GetLabel() const {
    return "Plane";
}


void PlaneInspectorAdapter::DrawInspectorUI()
{
    // -------- Size (geometry-affecting) --------
    float size = plane.GetSize();
    if (ImGui::DragFloat(
        "Size",
        &size,
        0.1f,
        0.1f,
        100.0f))
    {
        plane.SetSize(size);
        plane.RebuildMesh();   //  expensive work only when needed
    }

    ImGui::Separator();

    // -------- Material (PBR) --------
    Material& mat = *plane.GetMaterial();

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
    //glm::vec3 color = plane.GetColor();
    //if (ImGui::ColorEdit3("Color", &color.x)) {
    //    plane.SetColor(color); //  instant visual update
    //}


    //NO DELETION OF PLANE POSSIBLE
    /*ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.1725f, 0.2824f, 0.6588f, 1.0f });
    if (ImGui::Button("Delete Plane")) {
        deleteRequested = true;
    }
    ImGui::PopStyleColor();*/
}

bool PlaneInspectorAdapter::HasPendingChanges() const {
    return dirty;
}

void PlaneInspectorAdapter::ApplyChanges() {
    plane.SetSize(editSize);
    plane.SetColor(editColor);

    plane.RebuildMesh();   // important: expensive work happens once

    dirty = false;
}

bool PlaneInspectorAdapter::WantsDelete() const {
    return deleteRequested;
}
