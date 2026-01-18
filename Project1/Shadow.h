#pragma once
class Shadow {
public:
	virtual ~Shadow() = default; //default destructor

	virtual void RenderShadowMap() = 0;
	virtual unsigned GetShadowTexture() const = 0;
};