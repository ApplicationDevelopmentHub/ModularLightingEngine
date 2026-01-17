#include"Application.h"

LightHandle Application::AddLight(const Lightdata& dat) {
	return lightingSystem->AddLight(dat);
}
void Application::RemoveLight(LightHandle id){
	lightingSystem->RemoveLight(id);
}