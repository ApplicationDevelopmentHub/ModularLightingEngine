#include "UIHierarchyPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "EditorContext.h"
#include<string>

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

        // ---- Label (PrimitiveHandle is NOT an int) ----
        std::string label =
            std::string(primitive->GetTypeName()) + " " +
            std::to_string(id.value);

        // ---- Selection check (strong-handle safe) ----
        bool selected =
            ctx.GetSelectionType() == EditorContext::SelectionType::Primitive &&
            ctx.GetSelectedPrimitive().has_value() &&
            ctx.GetSelectedPrimitive()->value == id.value;

        // ---- Selection action ----
        if (ImGui::Selectable(label.c_str(), selected)) {
            ctx.SelectPrimitive(id);
        }
    }

    ImGui::EndChild();

    // ================= LIGHTS =================
    ImGui::BeginChild(
        "Hierarchy_Lights",
        ImVec2(0.0f, lightsHeight),
        true
    );

    ImGui::TextUnformatted("Lights");
    ImGui::Separator();

    bool hasLights = false;

    // -------- Directional Lights --------
    for (const auto& [id, light] : scene.GetDirectionalLights()) {
        hasLights = true;

        std::string label =
            "Directional Light " + std::to_string(id.value);

        bool selected =
            ctx.GetSelectionType() == EditorContext::SelectionType::Light &&
            ctx.GetSelectedLight().has_value() &&
            ctx.GetSelectedLight()->value == id.value;

        if (ImGui::Selectable(label.c_str(), selected)) {
            ctx.SelectLight(id);
        }
    }

    // -------- Point Lights --------
    /*for (const auto& [id, light] : scene.GetPointLights()) {
        hasLights = true;

        std::string label =
            "Point Light " + std::to_string(id.value);

        bool selected =
            ctx.GetSelectionType() == EditorContext::SelectionType::Light &&
            ctx.GetSelectedLight().has_value() &&
            ctx.GetSelectedLight()->value == id.value;

        if (ImGui::Selectable(label.c_str(), selected)) {
            ctx.SelectLight(id);
        }
    }*/

    // -------- Spot Lights --------
    for (const auto& [id, light] : scene.GetSpotLights()) {
        hasLights = true;

        std::string label =
            "Spot Light " + std::to_string(id.value);

        bool selected =
            ctx.GetSelectionType() == EditorContext::SelectionType::Light &&
            ctx.GetSelectedLight().has_value() &&
            ctx.GetSelectedLight()->value == id.value;

        if (ImGui::Selectable(label.c_str(), selected)) {
            ctx.SelectLight(id);
        }
    }

    if (!hasLights) {
        ImGui::TextDisabled("No lights in scene");
    }

    ImGui::EndChild();
    ImGui::End();
}

