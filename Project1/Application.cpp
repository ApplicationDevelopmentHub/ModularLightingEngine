#include"Application.h"
#include<GL/glew.h>
#include<iostream>

//Create objects of all subsystems using make_unique
//If any sub system init fails, return false: does not start application
bool Application::Init() {

	//----------GLFW WINDOW SUBSYSTEM-----
	window = std::make_unique<GLFWWindow>();
	if (!window->Create(1920, 1080, "Real Time Lighting Engine")) {
		return false;
	}

	//---------OPENGL LOADER-----------------
	//Whoever creates the OpenGL context is responsible
	// for initializing the OpenGL function loader.
	//GLFW is created here
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return false;
	}

	//-----------SCENE SUBSYSTEM-----------
	scene = std::make_unique<Scene>();

	//----------OPENGL RENDERER SUBSYSTEM-----
	renderer = std::make_unique<OpenGLRenderer>();

	//----------LIGHTING SUBSYSTEM---------

	//----------SHADOW SUBSYSTEM----------

	//-----------SUBSCRIBE OBSERVERS--------
	//Shadow subscribe to Light

	//UI subscriptions: IMgui

	//-------ENVIRONMENT: PLANE--------------
	CreatePlane(5.0f);

	//---------SUCCESS-----------------------
	running = true;
	return true;
}

//Application render loop: central handling
void Application::Run() {
	//GLFW window update every frame
	while (running && !window->ShouldClose()) {
		window->PollEvents();

		renderer->BeginFrame();
		renderer->Render(*scene);
		renderer->EndFrame();

		window->SwapBuffers();
	}
}

void Application::ShutDown() {

	//ENABLE LATER AFTER CONCERETE IMPLEMENTATIONS
	//unsubscribe all observers
	//lightingSystem->UnregisterObserver(shadowSystem.get());
}

PrimitiveHandle Application::CreatePlane(float size) {
	auto p = PrimitiveFactory::CreatePlane(size);
	return scene->AddPrimitive(std::move(p));
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