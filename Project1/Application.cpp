#include"Application.h"

bool Application::Init() {
	//GLFW Window: DONE
	//This is the foundation of application and will always be created
	window = std::make_unique<GLFWWindow>();
	if (!window->Create(1920, 1080, "Real Time Lighting Engine")) {
		return false;
	}
	running = true;
	return true;

	//ENABLE LATER WHEN CONCRETE IMPLEMENTATION DONE
	/*lightingSystem = std::make_unique<LightingSystem>();
	shadowSystem = std::make_unique<ShadowSystem>();*/

	//subscribe all observers
	//lightingSystem->RegisterObserver(shadowSystem.get());
}

//Application render loop: central handling
void Application::Run() {
	//GLFW window update every frame
	while (running && !window->ShouldClose()) {
		window->PollEvents();
		window->SwapBuffers();
	}
}

void Application::ShutDown() {

	//ENABLE LATER AFTER CONCERETE IMPLEMENTATIONS
	//unsubscribe all observers
	//lightingSystem->UnregisterObserver(shadowSystem.get());
}

LightHandle Application::AddLight(const Lightdata& dat) {

	//ENABLE LATER
	//return lightingSystem->AddLight(dat);
	return 0;
}
void Application::RemoveLight(LightHandle id){

	//ENABLE LATER
	//lightingSystem->RemoveLight(id);
}