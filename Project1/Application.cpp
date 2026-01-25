#include"Application.h"
#include<GL/glew.h>
#include<iostream>
#include<GLFW/glfw3.h>
#include"Input.h"

//Create objects of all subsystems using make_unique
//If any sub system init fails, return false: does not start application
bool Application::Init() {
	std::cout << "App facade init." << std::endl;
	//----------GLFW WINDOW SUBSYSTEM-----
	window = std::make_unique<GLFWWindow>();
	if (!window->Create(1920, 1080, "Real Time Lighting Engine")) {
		return false;
	}
	std::cout << "Glfw init success." << std::endl;

	//---------KEYBOARD INPUT SUBSYSTEM----------------
	Input::Init(
		static_cast<GLFWwindow*>(window->GetNativeHandle())
	);

	//---------OPENGL LOADER-----------------
	//Whoever creates the OpenGL context is responsible
	// for initializing the OpenGL function loader.
	//GLFW is created here
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return false;
	}
	std::cout << "Glew init success." << std::endl;

	//---------TIME INITIALIZATION-------------
	lastTime = glfwGetTime();

	//-----------SCENE SUBSYSTEM-----------
	scene = std::make_unique<Scene>();

	//----------OPENGL RENDERER SUBSYSTEM-----
	renderer = std::make_unique<OpenGLRenderer>();

	//--------CAMERA SUBSYSTEM OWNED BY RENDERER-----------
	float aspect = 1920.0f / 1080.0f;
	camera = std::make_unique<Camera>(aspect);

	cameraController = std::make_unique<CameraController>(*camera);

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
		float deltaTime = ComputeDeltaTime();
		window->PollEvents();

		Input::Update();
		cameraController->Update(deltaTime);

		renderer->BeginFrame();
		renderer->Render(*scene,*camera);
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
	std::cout << "Attempting primitive factory from facade" << std::endl;
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

float Application::ComputeDeltaTime() {
	double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;
	return deltaTime;
}