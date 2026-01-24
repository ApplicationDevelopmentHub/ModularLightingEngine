#pragma once

class Scene;

class Renderer {
public:
	virtual ~Renderer() = default;

	virtual void BeginFrame() = 0;
	virtual void Render(const Scene& scene) = 0;
	virtual void EndFrame()=0;

	virtual void BindMaterial() = 0;
private:
};
