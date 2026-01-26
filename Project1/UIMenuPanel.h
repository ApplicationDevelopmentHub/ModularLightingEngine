#pragma once
#include"UIPanel.h"
class UIMenuPanel:public UIPanel {
public:
	void Draw(Scene& scene, EditorContext& ctx) override;
};
