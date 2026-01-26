#include "UILatencyPanel.h"

#include <imgui.h>
#include <algorithm>

UILatencyPanel::UILatencyPanel(
    FrameTimingHistory& history,
    float targetFPS
)
    : timingHistory(history),
    targetFPS(targetFPS)
{
}
void UILatencyPanel::Draw(Scene&, EditorContext&) {

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float panelWidth = 300.0f;

    ImVec2 workPos = viewport->WorkPos;
    ImVec2 workSize = viewport->WorkSize;

    // Layout relative to Inspector panel
    const float inspectorHeight = workSize.y * 0.7f;
    const float gapHeight = workSize.y * 0.1f;
    const float latencyHeight = workSize.y * 0.2f;

    ImGui::SetNextWindowPos(
        ImVec2(
            workPos.x + workSize.x - panelWidth,
            workPos.y + inspectorHeight + gapHeight
        ),
        ImGuiCond_Always
    );

    ImGui::SetNextWindowSize(
        ImVec2(panelWidth, latencyHeight),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Latency", nullptr, flags);

    ImGui::Text("Frame Timing (ms)");
    ImGui::Separator();

    if (!timingHistory.HasData()) {
        ImGui::TextDisabled("Collecting frame data...");
        ImGui::End();
        return;
    }

    ImGui::Text("Current FPS : %.1f", timingHistory.GetCurrentFPS());
    ImGui::Text("Current CPU : %.2f ms", timingHistory.GetCurrentCPU());
    ImGui::Text("Current GPU : %.2f ms", timingHistory.GetCurrentGPU());

    ImGui::Separator();

    ImGui::Text("Avg CPU : %.2f ms", timingHistory.GetAvgCPU());
    ImGui::Text("Avg GPU : %.2f ms", timingHistory.GetAvgGPU());

    ImGui::Separator();

    if (!timingHistory.IsWarmupComplete()) {
        ImGui::TextDisabled("Warmup (%.1f s left)",
            5.0f - timingHistory.GetElapsedSeconds());
    }
    else {
        ImGui::Text("Worst CPU : %.2f ms", timingHistory.GetWorstCPU());
        ImGui::Text("Worst GPU : %.2f ms", timingHistory.GetWorstGPU());
        ImGui::Text("Worst FPS : %.1f", timingHistory.GetWorstFPS());
    }

    ImGui::End();
}
