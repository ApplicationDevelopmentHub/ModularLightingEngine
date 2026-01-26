#pragma once

#include "PrimitiveHandle.h"
#include "LightHandle.h"
#include "ShadowType.h"

#include <optional>
#include <variant>
#include<functional>

class EditorContext {
public:
    enum class SelectionType {
        None,
        Primitive,
        Light
    };

    // Selection control
    void SelectPrimitive(PrimitiveHandle id);
    void SelectLight(LightHandle id);
    void ClearSelection();

    // Query selection state
    SelectionType GetSelectionType() const;
    std::optional<PrimitiveHandle> GetSelectedPrimitive() const;
    std::optional<LightHandle> GetSelectedLight() const;

    //Command pattern

    //Create primitive request: encapsulate as an object
    std::function<void()> CreatePlane;
    std::function<void()> CreateSphere;
    std::function<void()> CreateCube;
    std::function<void()> CreateCone;

    //Lights
    std::function<void()> CreateDirectionalLight;
    std::function<void()> CreatePointLight;
    std::function<void()> CreateSpotLight;

    // Global overrides (editor-level)
    ShadowType globalShadowQuality = ShadowType::LowQuality;

private:
    SelectionType selectionType{ SelectionType::None };
    std::variant<std::monostate, PrimitiveHandle, LightHandle> selection;
};
