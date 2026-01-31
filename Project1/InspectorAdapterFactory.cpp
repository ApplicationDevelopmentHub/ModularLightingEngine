#include "InspectorAdapterFactory.h"

#include "EditorContext.h"
#include "IInspectorEditable.h"

// Engine
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"

// Inspector adapters
#include "PlaneInspectorAdapter.h"

std::unique_ptr<IInspectorEditable>
InspectorAdapterFactory::Create(Scene& scene, EditorContext& ctx)
{
    // We only support primitive selection for now
    if (ctx.GetSelectionType() != EditorContext::SelectionType::Primitive)
        return nullptr;

    auto idOpt = ctx.GetSelectedPrimitive();
    if (!idOpt)
        return nullptr;

    Primitive* primitive = scene.GetPrimitive(*idOpt);
    if (!primitive)
        return nullptr;

    // ---- Plane ----
    if (auto* plane = dynamic_cast<Plane*>(primitive)) {
        return std::make_unique<PlaneInspectorAdapter>(*plane);
    }

    // ---- Future primitives ----
    // if (auto* box = dynamic_cast<Box*>(primitive)) {
    //     return std::make_unique<BoxInspectorAdapter>(*box);
    // }

    return nullptr;
}
