#pragma once
#include<glm/glm.hpp>

class Scene;
class Camera;

class Renderer {
public:
	virtual ~Renderer() = default;

	virtual void BeginFrame() = 0;
	virtual void Render(const Scene& scene,const Camera& cam) = 0; //Render each primitive individually from the scene data
	virtual void EndFrame()=0;

	virtual void SetMVP(const glm::mat4& model)=0;
	virtual void SetColor(const glm::vec3& col)=0;
private:
};
