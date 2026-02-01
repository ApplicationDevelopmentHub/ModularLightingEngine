#pragma once
#include "IInspectorEditable.h"
#include "DirectionalLight.h"
#include "LightHandle.h"
#include "Scene.h"

class DirectionalLightInspectorAdapter final
    : public IInspectorEditable {
public:
    DirectionalLightInspectorAdapter(
        Scene& scene,
        LightHandle id);

    const char* GetLabel() const override;
    void DrawInspectorUI() override;

    bool HasPendingChanges() const override { return false; }
    void ApplyChanges() override {}

    bool WantsDelete() const override { return deleteRequested; }

private:
    Scene& scene;
    LightHandle id;
    bool deleteRequested{ false };
};
