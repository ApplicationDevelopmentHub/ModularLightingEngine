#pragma once
#include"PrimitiveHandle.h"
#include"LightHandle.h"
#include<optional>
#include<variant>
#include"ShadowType.h"

class EditorContext {
public:
    enum class SelectionType {
        None,
        Primitive,
        Light
    };

    void SelectPrimitive(PrimitiveHandle id);
    void SelectLight(LightHandle id);
    void ClearSelection();

    SelectionType GetSelectionType() const;

    std::optional<PrimitiveHandle> GetSelectedPrimitive() const;
    std::optional<LightHandle> GetSelectedLight() const;

    // Global overrides
    ShadowType globalShadowQuality = ShadowType::LowQuality; //Default low has to be set
private:
    SelectionType selectionType{ SelectionType::None };
    std::variant<std::monostate, PrimitiveHandle, LightHandle> selection;
};
