#include "UIHierarchyPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "EditorContext.h"

void UIHierarchyPanel::Draw(Scene& scene, EditorContext& ctx) {

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float hierarchyWidth = 300.0f;   // as requested

    ImVec2 workPos = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    // ----- FIX POSITION (LEFT) -----
    ImGui::SetNextWindowPos(
        ImVec2(workPos.x, workPos.y),
        ImGuiCond_Always
    );

    // ----- FIX SIZE -----
    ImGui::SetNextWindowSize(
        ImVec2(hierarchyWidth, workSize.y),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Hierarchy", nullptr, flags);

    // --- Minimal content (30px wide = icons only) ---
    ImGui::Text("H");

    ImGui::Separator();

    // Example placeholders (icons / initials)
    ImGui::Text("P");
    ImGui::Text("L");

    ImGui::End();
}
