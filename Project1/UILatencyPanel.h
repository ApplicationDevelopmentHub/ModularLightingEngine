#pragma once
#include"UIPanel.h"
#include"FrameTimingHistory.h"

class UILatencyPanel :public UIPanel {
public:
	explicit UILatencyPanel(FrameTimingHistory& history,
		float targetFPS = 120.0f);
	void Draw(Scene& scene, EditorContext& ctx) override;
private:
	FrameTimingHistory& timingHistory;
	float targetFPS;
};
