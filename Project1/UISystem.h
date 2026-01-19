#pragma once
#include"IWindow.h"
#include<memory>
#include"UIPanel.h"
#include<vector>

class UISystem {
public:
	void Init();
	void BeginFrame();
	void DrawFrame();
	void EndFrame();
	void AddPanel(std::unique_ptr<UIPanel> panel);
private:
	std::vector<std::unique_ptr<UIPanel>> panels;
};
