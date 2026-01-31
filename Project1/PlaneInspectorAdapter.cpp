#include "PlaneInspectorAdapter.h"
#include <imgui.h>

//PlaneInspectorAdapter::PlaneInspectorAdapter(Plane& plane)
//    : plane(plane),
//    editSize(plane.GetSize()),
//    editColor(plane.GetColor()) {
//}

PlaneInspectorAdapter::PlaneInspectorAdapter(Plane& plane)
    : plane(plane) {
}

const char* PlaneInspectorAdapter::GetLabel() const {
    return "Plane";
}

//void PlaneInspectorAdapter::DrawInspectorUI() {
//    dirty |= ImGui::DragFloat(
//        "Size",
//        &editSize,
//        0.1f,
//        0.1f,
//        100.0f
//    );
//
//    dirty |= ImGui::ColorEdit3(
//        "Color",
//        &editColor.x
//    );
//}

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

    // -------- Color (cheap, visual-only) --------
    glm::vec3 color = plane.GetColor();
    if (ImGui::ColorEdit3("Color", &color.x)) {
        plane.SetColor(color); //  instant visual update
    }
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
