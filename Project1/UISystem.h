#pragma once
#include"IWindow.h"
#include<memory>
#include"UIPanel.h"
#include<vector>
#include"EditorContext.h"

//forward declerations
class Scene;
class UIPanel;

class UISystem {
public:
	void Init();
	void BeginFrame();
	void DrawFrame(Scene& scene);
	void EndFrame();
	void AddPanel(std::unique_ptr<UIPanel> panel);
	EditorContext& GetEditorContext();
private:
	std::vector<std::unique_ptr<UIPanel>> panels;
	EditorContext editorContext;
};
