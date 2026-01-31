#pragma once

#include "IInspectorEditable.h"
#include "Plane.h"          // your engine Plane class
#include <glm/vec3.hpp>

class PlaneInspectorAdapter final : public IInspectorEditable {
public:
    explicit PlaneInspectorAdapter(Plane& plane);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

private:
    Plane& plane;

    // Inspector buffer (editable copy)
    float editSize;
    glm::vec3 editColor;

    bool dirty = false;
};
