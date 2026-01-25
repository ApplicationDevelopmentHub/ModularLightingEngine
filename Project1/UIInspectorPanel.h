#pragma once
#include"UIPanel.h"
#include"EditorContext.h"
class UIInspectorPanel:public UIPanel {
public:
	void Draw(Scene& scene, EditorContext& ctx) override;
};
