#include "EditorContext.h"

void EditorContext::SelectPrimitive(PrimitiveHandle id) {
    selectionType = SelectionType::Primitive;
    selection = id;
}

void EditorContext::SelectLight(LightHandle id) {
    selectionType = SelectionType::Light;
    //selection = id;
}

void EditorContext::ClearSelection() {
    selectionType = SelectionType::None;
    selection = std::monostate{};
}

EditorContext::SelectionType
EditorContext::GetSelectionType() const {
    return selectionType;
}

std::optional<PrimitiveHandle>
EditorContext::GetSelectedPrimitive() const {
    if (selectionType == SelectionType::Primitive) {
        return std::get<PrimitiveHandle>(selection);
    }
    return std::nullopt;
}

std::optional<LightHandle>
EditorContext::GetSelectedLight() const {
    /*if (selectionType == SelectionType::Light) {
        return std::get<LightHandle>(selection);
    }*/
    return std::nullopt;
}

//std::optional<uint32_t> EditorContext::GetSelectedId() const {
//    if (selectionType == SelectionType::None)
//        return std::nullopt;
//
//    return std::get<uint32_t>(selection);
//}
