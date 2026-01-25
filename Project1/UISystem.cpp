#include"UISystem.h"
#include<iostream>

void UISystem::Init() {
    std::cout << "UI system init success." << std::endl;
}

void UISystem::BeginFrame() {
    // ImGui::NewFrame() already called in Application
}

void UISystem::DrawFrame(Scene& scene) {
    for (auto& panel : panels) {
        panel->Draw(scene, editorContext);
    }
}

void UISystem::EndFrame() {
    // nothing yet
}

void UISystem::AddPanel(std::unique_ptr<UIPanel> panel) {
    panels.emplace_back(std::move(panel));
}
