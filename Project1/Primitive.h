#pragma once
#include"Renderer.h"

class Primitive {
public:
	virtual~Primitive() = default;
	virtual const char* GetTypeName() const = 0;
	virtual void Draw(Renderer& renderer) const = 0; //sets MVP for each primitive
private:
};
