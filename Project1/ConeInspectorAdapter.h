#pragma once

#include "IInspectorEditable.h"
#include "Cone.h"          // your engine Plane class
#include <glm/vec3.hpp>
#include"PrimitiveHandle.h"

class ConeInspectorAdapter final : public IInspectorEditable {
public:
    explicit ConeInspectorAdapter(Cone& cone, PrimitiveHandle id);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

    bool WantsDelete() const override;

private:
    Cone& cone;
    PrimitiveHandle id;
    bool deleteRequested = false;
};
