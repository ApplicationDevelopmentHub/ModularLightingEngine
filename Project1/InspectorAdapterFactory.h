#pragma once

#include <memory>

class Scene;
class EditorContext;
class IInspectorEditable;

class InspectorAdapterFactory {
public:
    static std::unique_ptr<IInspectorEditable>
        Create(Scene& scene, EditorContext& ctx);
};
