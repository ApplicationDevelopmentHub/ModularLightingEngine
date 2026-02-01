#pragma once

#include "PrimitiveHandle.h"
#include"LightHandle.h"
#include <optional>
#include <variant>
#include<functional>
#include<cstdint>

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
    std::optional<LightHandle>     GetSelectedLight() const;

    //COMMAND PATTERN IN APPLICATION FACADE
    //Create primitive request: encapsulate as an object
    std::function<void()> CreatePlane;
    std::function<void()> CreateSphere;
    std::function<void()> CreateBox;
    std::function<void()> CreateCone;

    std::function<void(PrimitiveHandle) > DeleteSelectedPrimitive;

    //Lights
    std::function<void()> CreateDirectionalLight;
    std::function<void()> CreatePointLight;
    std::function<void()> CreateSpotLight;

    std::function<void(LightHandle)> DeleteSelectedLight;

private:
    SelectionType selectionType{ SelectionType::None };
    std::variant<std::monostate, PrimitiveHandle,LightHandle> selection;
};
