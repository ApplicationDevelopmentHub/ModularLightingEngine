#pragma once

class Scene;
class EditorContext;

class UIPanel {
public:
	virtual ~UIPanel() = default;
	virtual void Draw(Scene& scene,EditorContext& context) = 0;
};
