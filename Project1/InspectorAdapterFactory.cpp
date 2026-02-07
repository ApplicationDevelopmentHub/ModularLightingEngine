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

// Lights
#include "DirectionalLightInspectorAdapter.h"
//#include "PointLightInspectorAdapter.h"
#include "SpotLightInspectorAdapter.h"

std::unique_ptr<IInspectorEditable>
InspectorAdapterFactory::Create(Scene& scene, EditorContext& ctx)
{
    using SelectionType = EditorContext::SelectionType;

    // =====================================================
    // PRIMITIVES
    // =====================================================
    if (ctx.GetSelectionType() == SelectionType::Primitive) {

        auto idOpt = ctx.GetSelectedPrimitive();
        if (!idOpt)
            return nullptr;

        Primitive* primitive = scene.GetPrimitive(*idOpt);
        if (!primitive)
            return nullptr;

        if (auto* plane = dynamic_cast<Plane*>(primitive)) {
            return std::make_unique<PlaneInspectorAdapter>(*plane, *idOpt);
        }

        if (auto* sphere = dynamic_cast<Sphere*>(primitive)) {
            return std::make_unique<SphereInspectorAdapter>(*sphere, *idOpt);
        }

        if (auto* box = dynamic_cast<Box*>(primitive)) {
            return std::make_unique<BoxInspectorAdapter>(*box, *idOpt);
        }

        if (auto* cone = dynamic_cast<Cone*>(primitive)) {
            return std::make_unique<ConeInspectorAdapter>(*cone, *idOpt);
        }

        return nullptr;
    }

    // =====================================================
    // LIGHTS
    // =====================================================
    if (ctx.GetSelectionType() == EditorContext::SelectionType::Light) {
        auto lightId = ctx.GetSelectedLight();
        if (!lightId)
            return nullptr;

        if (scene.GetDirectionalLight(*lightId)) {
            return std::make_unique<DirectionalLightInspectorAdapter>(
                scene,
                *lightId
            );
        }

        if (scene.GetSpotLight(*lightId)) {
            return std::make_unique<SpotLightInspectorAdapter>(
                scene,
                *lightId
            );
        }
    }

    return nullptr;
}
