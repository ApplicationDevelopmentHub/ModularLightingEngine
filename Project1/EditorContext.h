#pragma once

#include "PrimitiveHandle.h"
#include "LightHandle.h"
#include "ShadowType.h"

#include <optional>
#include <variant>

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

    // Global overrides (editor-level)
    ShadowType globalShadowQuality = ShadowType::LowQuality;

private:
    SelectionType selectionType{ SelectionType::None };
    std::variant<std::monostate, PrimitiveHandle, LightHandle> selection;
};
