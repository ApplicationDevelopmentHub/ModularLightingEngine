#pragma once
class UIPanel {
public:
	virtual ~UIPanel() = default;
	virtual void Draw() = 0;
};
