#pragma once

#include "IInspectorEditable.h"
#include "Sphere.h"          // your engine Plane class
#include <glm/vec3.hpp>

class SphereInspectorAdapter final : public IInspectorEditable {
public:
    explicit SphereInspectorAdapter(Sphere& sphere);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

private:
    Sphere& sphere;

    // Inspector buffer (editable copy)
    std::uint32_t editStacks;
    std::uint32_t editSectors;
    glm::vec3 editColor;

    bool dirty = false;
};
