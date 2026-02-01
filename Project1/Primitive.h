#pragma once
#include"Renderer.h"
#include"Material.h"
#include<memory>

//class Material;

class Primitive {
public:
	virtual~Primitive() = default;
	virtual const char* GetTypeName() const = 0;
	virtual void Draw(Renderer& renderer) const = 0; //sets MVP for each primitive

	// ---- Material access ----
	std::shared_ptr<Material> GetMaterial() const { return material; }
	void SetMaterial(const std::shared_ptr<Material>& mat) { material = mat; }
private:
protected:
	Primitive()
		: material(std::make_shared<Material>()) // ✅ GUARANTEE
	{
	}

	std::shared_ptr<Material> material;
};
