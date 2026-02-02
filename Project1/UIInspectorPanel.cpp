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

    ImVec2 workPos  = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    ImGui::SetNextWindowPos(
        ImVec2(workPos.x + workSize.x - panelWidth, workPos.y),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ImVec2(panelWidth, workSize.y * 0.8f),
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

    static PrimitiveHandle lastPrimitiveId{};
    static LightHandle     lastLightId{};

    //static PrimitiveHandle lastId{}; // value = 0

    const auto currentType = ctx.GetSelectionType();
    //const auto currentId   = ctx.GetSelectedPrimitive();

    bool selectionChanged = (currentType != lastType);

   /* const bool selectionChanged =
        currentType != lastType ||
        currentId.has_value() != (lastId.value != 0) ||
        (currentId.has_value() && currentId->value != lastId.value);*/

    /*if (selectionChanged) {
        adapter = InspectorAdapterFactory::Create(scene, ctx);
        lastType = currentType;
        lastId   = currentId.value_or(PrimitiveHandle{});
    }*/

    if (!selectionChanged)
    {
        if (currentType == EditorContext::SelectionType::Primitive)
        {
            auto cur = ctx.GetSelectedPrimitive();
            if (!cur || cur->value != lastPrimitiveId.value)
                selectionChanged = true;
        }
        else if (currentType == EditorContext::SelectionType::Light)
        {
            auto cur = ctx.GetSelectedLight();
            if (!cur || cur->value != lastLightId.value)
                selectionChanged = true;
        }
    }

    if (selectionChanged)
    {
        adapter = InspectorAdapterFactory::Create(scene, ctx);
        lastType = currentType;

        if (currentType == EditorContext::SelectionType::Primitive)
        {
            lastPrimitiveId =
                ctx.GetSelectedPrimitive().value_or(PrimitiveHandle{});
        }
        else if (currentType == EditorContext::SelectionType::Light)
        {
            lastLightId =
                ctx.GetSelectedLight().value_or(LightHandle{});
        }
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
    //if (adapter->WantsDelete()) {
    //    auto id = ctx.GetSelectedPrimitive();
    //    if (id && ctx.DeleteSelectedPrimitive) {
    //        ctx.DeleteSelectedPrimitive(*id);
    //    }

    //    ctx.ClearSelection();
    //    adapter.reset();

    //    ImGui::End();
    //    return; // IMPORTANT: stop drawing this frame
    //}
    if (adapter->WantsDelete())
    {
        if (ctx.GetSelectionType() == EditorContext::SelectionType::Primitive)
        {
            auto id = ctx.GetSelectedPrimitive();
            if (id && ctx.DeleteSelectedPrimitive)
                ctx.DeleteSelectedPrimitive(*id);
        }
        else if (ctx.GetSelectionType() == EditorContext::SelectionType::Light)
        {
            auto id = ctx.GetSelectedLight();
            if (id && ctx.DeleteSelectedLight)
                ctx.DeleteSelectedLight(*id);
        }

        ctx.ClearSelection();
        adapter.reset();

        ImGui::End();
        return;
    }

    ImGui::End();
}
