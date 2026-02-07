#include "UIMenuPanel.h"
#include <imgui.h>
#include "Scene.h"
#include "EditorContext.h"

void UIMenuPanel::Draw(Scene&, EditorContext& ctx) {

    if (ImGui::BeginMainMenuBar()) {
        ImGui::SetCursorPosX(300.0f);

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Primitive")) {
            /*if (ImGui::MenuItem("Plane")) {
                if (ctx.CreatePlane)
                    ctx.CreatePlane();
            }*/

            if (ImGui::MenuItem("Box")) {
                if (ctx.CreateBox)
                    ctx.CreateBox();
            }

            if (ImGui::MenuItem("Sphere")) {
                if (ctx.CreateSphere)
                    ctx.CreateSphere();
            }

            if (ImGui::MenuItem("Cone")) {
                if (ctx.CreateCone)
                    ctx.CreateCone();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Light")) {
            if (ImGui::MenuItem("Directional")) {
                if (ctx.CreateDirectionalLight)
                    ctx.CreateDirectionalLight();
            }
            ImGui::MenuItem("Point");
            if(ImGui::MenuItem("Spot")) {
                if (ctx.CreateSpotLight)
                    ctx.CreateSpotLight();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

