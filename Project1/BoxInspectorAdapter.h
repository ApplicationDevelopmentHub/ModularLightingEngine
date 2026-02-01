#pragma once

#include "IInspectorEditable.h"
#include "Box.h"          // your engine Plane class
#include <glm/vec3.hpp>
#include"PrimitiveHandle.h"

class BoxInspectorAdapter final : public IInspectorEditable {
public:
    explicit BoxInspectorAdapter(Box& box, PrimitiveHandle id);

    const char* GetLabel() const override;

    void DrawInspectorUI() override;
    bool HasPendingChanges() const override;
    void ApplyChanges() override;

    bool WantsDelete() const override;

private:
    Box& box;
    PrimitiveHandle id;
    bool deleteRequested = false;
};
