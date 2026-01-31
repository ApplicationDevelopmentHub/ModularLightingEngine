#include "UIInspectorPanel.h"

#include <imgui.h>
#include <memory>

#include "Scene.h"
#include "EditorContext.h"
#include "PrimitiveHandle.h"

#include "InspectorAdapterFactory.h"
#include "IInspectorEditable.h"

void UIInspectorPanel::Draw(Scene& scene, EditorContext& ctx)
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float panelWidth = 300.0f;

    ImVec2 workPos = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    ImGui::SetNextWindowPos(
        ImVec2(workPos.x + workSize.x - panelWidth, workPos.y),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ImVec2(panelWidth, workSize.y),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Inspector", nullptr, flags);

    // ------------------------------------------------------------
    // Persistent inspector adapter (critical for runtime editing)
    // ------------------------------------------------------------

    static std::unique_ptr<IInspectorEditable> adapter;
    static EditorContext::SelectionType lastType =
        EditorContext::SelectionType::None;
    static PrimitiveHandle lastId{}; // value = 0

    const auto currentType = ctx.GetSelectionType();
    const auto currentId = ctx.GetSelectedPrimitive();

    const bool selectionChanged =
        currentType != lastType ||
        currentId.has_value() != (lastId.value != 0) ||
        (currentId.has_value() && currentId->value != lastId.value);

    if (selectionChanged) {
        adapter = InspectorAdapterFactory::Create(scene, ctx);
        lastType = currentType;
        lastId = currentId.value_or(PrimitiveHandle{});
    }

    // ------------------------------------------------------------
    // Draw inspector contents
    // ------------------------------------------------------------

    if (!adapter) {
        ImGui::TextDisabled("Nothing selected");
        ImGui::End();
        return;
    }

    ImGui::TextUnformatted(adapter->GetLabel());
    ImGui::Separator();

    adapter->DrawInspectorUI();

    /*if (adapter->HasPendingChanges()) {
        ImGui::Separator();
        if (ImGui::Button("Apply")) {
            adapter->ApplyChanges();
        }
    }*/

    ImGui::End();
}
