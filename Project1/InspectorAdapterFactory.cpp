#include "InspectorAdapterFactory.h"

#include "EditorContext.h"
#include "IInspectorEditable.h"

// Engine
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"
#include"Sphere.h"
#include"Cone.h"
#include"Box.h"

// Inspector adapters
#include "PlaneInspectorAdapter.h"
#include"SphereInspectorAdapter.h"
#include"BoxInspectorAdapter.h"
#include"ConeInspectorAdapter.h"

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
        return std::make_unique<PlaneInspectorAdapter>(*plane, *idOpt);
    }

    //Sphere
    if (auto* sphere = dynamic_cast<Sphere*>(primitive)) {
        return std::make_unique<SphereInspectorAdapter>(*sphere, *idOpt);
    }

    //Box
    if (auto* box = dynamic_cast<Box*>(primitive)) {
        return std::make_unique<BoxInspectorAdapter>(*box, *idOpt);
    }

    //Cone
    if (auto* cone = dynamic_cast<Cone*>(primitive)) {
        return std::make_unique<ConeInspectorAdapter>(*cone, *idOpt);
    }

    // ---- Future primitives ----
    // if (auto* box = dynamic_cast<Box*>(primitive)) {
    //     return std::make_unique<BoxInspectorAdapter>(*box);
    // }

    return nullptr;
}
