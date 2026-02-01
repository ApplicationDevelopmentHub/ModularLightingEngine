#pragma once

#include "IInspectorEditable.h"
#include "Sphere.h"          // your engine Plane class
#include <glm/vec3.hpp>
#include"PrimitiveHandle.h"

class SphereInspectorAdapter final : public IInspectorEditable {
public:
    explicit SphereInspectorAdapter(Sphere& sphere, PrimitiveHandle id);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

    bool WantsDelete() const override;

private:
    Sphere& sphere;
    PrimitiveHandle id;
    bool deleteRequested = false;

    // Inspector buffer (editable copy)
    std::uint32_t editStacks;
    std::uint32_t editSectors;
    glm::vec3 editColor;

    bool dirty = false;
};
