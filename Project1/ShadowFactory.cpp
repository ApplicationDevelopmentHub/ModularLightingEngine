#include"ShadowFactory.h"

//std::unique_ptr<Shadow> ShadowFactory::CreateShadow(LightType light, ShadowType shadow) {
//	//handle the no shadow case
//	if (shadow == ShadowType::None) return nullptr;
//
//	switch (shadow) {
//	case ShadowType::LowQuality:
//		return std::make_unique<LowQualityShadow>(1024,1);
//		break;
//	case ShadowType::MediumQuality:
//		return std::make_unique<MediumQualityShadow>(2048, 1);
//		break;
//	case ShadowType::HighQuality:
//		return std::make_unique<HighQualityShadow>(4096, 1);
//			break;
//	default:
//		return nullptr;
//		break;
//	}
//}

//PCF shadow: percentage closer fitting