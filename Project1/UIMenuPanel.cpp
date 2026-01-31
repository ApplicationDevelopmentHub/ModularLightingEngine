#include "UIMenuPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "EditorContext.h"
#include "ShadowType.h"

void UIMenuPanel::Draw(Scene&, EditorContext& ctx) {

    if (ImGui::BeginMainMenuBar()) {
        ImGui::SetCursorPosX(300.0f);

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Primitive")) {
            if (ImGui::MenuItem("Plane")) {
                if (ctx.CreatePlane)
                    ctx.CreatePlane();
            }

            if (ImGui::MenuItem("Box")) {
                if (ctx.CreateBox)
                    ctx.CreateBox();
            }

            if (ImGui::MenuItem("Sphere")) {
                if (ctx.CreateSphere)
                    ctx.CreateSphere();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Light")) {
            ImGui::MenuItem("Directional");
            ImGui::MenuItem("Point");
            ImGui::MenuItem("Spot");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Shadow")) {
            int q = static_cast<int>(ctx.globalShadowQuality);
            ImGui::Combo("Quality", &q,
                "None\0Low\0Medium\0High\0");
            ctx.globalShadowQuality =
                static_cast<ShadowType>(q);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

