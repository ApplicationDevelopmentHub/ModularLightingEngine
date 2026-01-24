#pragma once
#include"Renderer.h"

class Primitive {
public:
	virtual~Primitive() = default;
	virtual void Draw(Renderer& renderer) const = 0;
private:
};
