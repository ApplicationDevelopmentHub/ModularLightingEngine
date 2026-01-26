#pragma once
#include"UIPanel.h"
class UIHierarchyPanel:public UIPanel {
public:
	void Draw(Scene& scene, EditorContext& context) override;
};
