#include "UIInspectorPanel.h"
#include <imgui.h>
#include "Scene.h"
#include"ShadowType.h"

//void UIInspectorPanel::Draw(Scene& scene, EditorContext& ctx) {
//
//    ImGuiViewport* viewport = ImGui::GetMainViewport();
//
//    const float inspectorWidth = 300.0f;
//
//    // Work area excludes menu bar & docking
//    ImVec2 workPos = viewport->WorkPos;
//    ImVec2 workSize = viewport->WorkSize;
//
//    ImGui::SetNextWindowPos(
//        ImVec2(workPos.x + workSize.x - inspectorWidth, workPos.y),
//        ImGuiCond_Always
//    );
//
//    ImGui::SetNextWindowSize(
//        ImVec2(inspectorWidth, workSize.y),
//        ImGuiCond_Always
//    );
//
//    ImGuiWindowFlags flags =
//        ImGuiWindowFlags_NoMove |
//        ImGuiWindowFlags_NoResize |
//        ImGuiWindowFlags_NoCollapse |
//        ImGuiWindowFlags_NoBringToFrontOnFocus;
//
//    ImGui::Begin("Inspector", nullptr, flags);
//
//    switch (ctx.GetSelectionType()) {
//
//    case EditorContext::SelectionType::Primitive: {
//        auto id = ctx.GetSelectedPrimitive().value();
//        // draw primitive inspector
//        ImGui::Text("Primitive ID: %u", id);
//        break;
//    }
//
//    case EditorContext::SelectionType::Light: {
//        auto id = ctx.GetSelectedLight().value();
//        ImGui::Text("Light ID: %u", id);
//
//        ImGui::Separator();
//        ImGui::Text("Shadows");
//
//        int q = static_cast<int>(ctx.globalShadowQuality);
//        ImGui::Combo("Quality", &q,
//            "None\0Low\0Medium\0High\0");
//        ctx.globalShadowQuality =
//            static_cast<ShadowType>(q);
//
//        break;
//    }
//
//    default:
//        ImGui::TextDisabled("Nothing selected");
//        break;
//    }
//
//    ImGui::End();
//}

#include "UIInspectorPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "ShadowType.h"

void UIInspectorPanel::Draw(Scene& scene, EditorContext& ctx) {

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float panelWidth = 300.0f;

    ImVec2 workPos = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    const float inspectorHeight = workSize.y * 0.8f;

    ImGui::SetNextWindowPos(
        ImVec2(workPos.x + workSize.x - panelWidth, workPos.y),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ImVec2(panelWidth, inspectorHeight),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Inspector", nullptr, flags);

    switch (ctx.GetSelectionType()) {

    case EditorContext::SelectionType::Primitive: {
        if (auto id = ctx.GetSelectedPrimitive()) {
            ImGui::Text("Primitive ID: %u", *id);
        }
        break;
    }

    case EditorContext::SelectionType::Light: {
        if (auto id = ctx.GetSelectedLight()) {
            ImGui::Text("Light ID: %u", *id);
        }

        ImGui::Separator();
        ImGui::Text("Shadows");

        int q = static_cast<int>(ctx.globalShadowQuality);
        if (ImGui::Combo("Quality", &q, "None\0Low\0Medium\0High\0")) {
            ctx.globalShadowQuality = static_cast<ShadowType>(q);
        }
        break;
    }

    default:
        ImGui::TextDisabled("Nothing selected");
        break;
    }

    ImGui::End();
}

