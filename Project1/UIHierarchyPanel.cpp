#include "UIHierarchyPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "EditorContext.h"
#include<string>

//void UIHierarchyPanel::Draw(Scene&, EditorContext&)
//{
//    ImGuiViewport* viewport = ImGui::GetMainViewport();
//
//    const float hierarchyWidth = 300.0f;
//
//    ImVec2 workPos = viewport->WorkPos;
//    ImVec2 workSize = viewport->WorkSize;
//
//    // ---- Fixed position (LEFT) ----
//    ImGui::SetNextWindowPos(
//        ImVec2(workPos.x, workPos.y),
//        ImGuiCond_Always
//    );
//
//    // ---- Fixed size ----
//    ImGui::SetNextWindowSize(
//        ImVec2(hierarchyWidth, workSize.y),
//        ImGuiCond_Always
//    );
//
//    ImGuiWindowFlags flags =
//        ImGuiWindowFlags_NoMove |
//        ImGuiWindowFlags_NoResize |
//        ImGuiWindowFlags_NoCollapse |
//        ImGuiWindowFlags_NoBringToFrontOnFocus;
//
//    ImGui::Begin("Hierarchy", nullptr, flags);
//
//    // Available height INSIDE the window
//    float totalHeight = ImGui::GetContentRegionAvail().y;
//
//    float primitivesHeight = totalHeight * 0.3f;
//    float lightsHeight = totalHeight * 0.7f;
//
//    // ---------- Primitives (Top 30%) ----------
//    ImGui::BeginChild(
//        "Hierarchy_Primitives",
//        ImVec2(0.0f, primitivesHeight),
//        true
//    );
//
//    ImGui::TextUnformatted("Primitives");
//    ImGui::Separator();
//
//    ImGui::EndChild();
//
//    // ---------- Lights (Bottom 70%) ----------
//    ImGui::BeginChild(
//        "Hierarchy_Lights",
//        ImVec2(0.0f, lightsHeight),
//        true
//    );
//
//    ImGui::TextUnformatted("Lights");
//    ImGui::Separator();
//
//    ImGui::EndChild();
//
//    ImGui::End();
//}

void UIHierarchyPanel::Draw(Scene& scene, EditorContext& ctx)
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float hierarchyWidth = 300.0f;

    ImVec2 workPos = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    ImGui::SetNextWindowPos(
        ImVec2(workPos.x, workPos.y),
        ImGuiCond_Always
    );

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

    float totalHeight = ImGui::GetContentRegionAvail().y;
    float primitivesHeight = totalHeight * 0.3f;
    float lightsHeight = totalHeight * 0.7f;

    // ================= PRIMITIVES =================
    ImGui::BeginChild(
        "Hierarchy_Primitives",
        ImVec2(0.0f, primitivesHeight),
        true
    );

    ImGui::TextUnformatted("Primitives");
    ImGui::Separator();

    for (const auto& [id, primitive] : scene.GetPrimitives()) {

        std::string label =
            std::string(primitive->GetTypeName()) + " " +
            std::to_string(id);

        bool selected =
            ctx.GetSelectionType() == EditorContext::SelectionType::Primitive &&
            ctx.GetSelectedPrimitive().has_value() &&
            ctx.GetSelectedPrimitive().value() == id;

        if (ImGui::Selectable(label.c_str(), selected)) {
            ctx.SelectPrimitive(id);
        }
    }

    ImGui::EndChild();

    // ================= LIGHTS (EMPTY FOR NOW) =================
    ImGui::BeginChild(
        "Hierarchy_Lights",
        ImVec2(0.0f, lightsHeight),
        true
    );

    ImGui::TextUnformatted("Lights");
    ImGui::Separator();

    ImGui::TextDisabled("No lights implemented");

    ImGui::EndChild();

    ImGui::End();
}

