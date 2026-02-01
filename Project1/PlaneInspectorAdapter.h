#pragma once

#include "IInspectorEditable.h"
#include "Plane.h"          // your engine Plane class
#include <glm/vec3.hpp>
#include"PrimitiveHandle.h"

class PlaneInspectorAdapter final : public IInspectorEditable {
public:
    explicit PlaneInspectorAdapter(Plane& plane, PrimitiveHandle id);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

    bool WantsDelete() const override;

private:
    Plane& plane;
    PrimitiveHandle id;
    bool deleteRequested = false;

    // Inspector buffer (editable copy)
    float editSize;
    glm::vec3 editColor;

    bool dirty = false;
};
