#include"Application.h"
#include<GL/glew.h>
#include<iostream>
#include<GLFW/glfw3.h>
#include"Input.h"

//Create objects of all subsystems using make_unique
//If any sub system init fails, return false: does not start application
bool Application::Init() {

	std::cout << "App facade init." << std::endl;

	//GLFW WINDOW SUBSYSTEM

	window = std::make_unique<GLFWWindow>();
	if (!window->Create(1920, 1080, "Real Time Lighting Engine")) {
		return false;
	}
	std::cout << "Glfw init success." << std::endl;

	//KEYBOARD INPUT SUBSYSTEM

	Input::Init(
		static_cast<GLFWwindow*>(window->GetNativeHandle())
	);

	//OPENGL LOADER
	// OpenGL is init at same place as GLFW
	// Agency creating OpenGL context responsible for OpenGL function loader

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return false;
	}
	std::cout << "Glew init success." << std::endl;

	//TIME INITIALIZATION FOR LATENCY AND OTHER USE

	lastTime = glfwGetTime();

	//SCENE SUBSYSTEM

	scene = std::make_unique<Scene>();

	//OPENGL RENDERER SUBSYSTEM
	renderer = std::make_unique<OpenGLRenderer>();

	//CAMERA SUBSYSTEM OWNED BY RENDERER
	float aspect = 1920.0f / 1080.0f;
	camera = std::make_unique<Camera>(aspect); //renderer can directly use this camera as a function parameter
	cameraController = std::make_unique<CameraController>(*camera);

	//IMGUI SUBSYSTEM

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	GLFWwindow* glfwWindow =
		static_cast<GLFWwindow*>(window->GetNativeHandle());

	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	uiSystem = std::make_unique<UISystem>();
	uiSystem->Init();

	uiSystem->AddPanel(std::make_unique<UIInspectorPanel>()); //Inspector panel right
	uiSystem->AddPanel(std::make_unique<UIHierarchyPanel>()); //Hierarchy panel left
	uiSystem->AddPanel(std::make_unique<UIMenuPanel>()); //top menu bar
	uiSystem->AddPanel(std::make_unique<UILatencyPanel>(frameTimingHistory,120.0f)); //below inspector
		
	//EDITOR CONTEXT: COMMAND PATTERN

	EditorContext& ctx = uiSystem->GetEditorContext();
	ctx.CreateSphere = [this]() { //create sphere primitive
		CreateSphere(1.0f, 32, 64);
		};

	//Primitives
	ctx.CreateBox = [this]() { //create box primitive
		CreateBox(1.0f, 1.0f, 1.0f);
		};

	ctx.CreateCone = [this]() { //create cone primitive
		CreateCone(1.0f, 1.5f, 32.0f);
		};

	ctx.DeleteSelectedPrimitive = [this](PrimitiveHandle id) { //Delete any primitive
		scene->RemovePrimitive(id);
		};

	//Lights
	ctx.CreateDirectionalLight = [this]() { //create directional light
		CreateDirectionalLight();
		};

	ctx.CreateSpotLight = [this]() { //create spot light
		CreateSpotLight();
		};

	ctx.CreatePointLight = [this]() { //create spot light
		CreatePointLight();
		};

	ctx.DeleteSelectedLight = [this](LightHandle id) {
		scene->RemoveLight(id);
		};

	//CREATE FUNDAMENTAL PLANE
	CreatePlane(8.0f);

	//FACADE SUCCESS
	std::cout << "All susbystems successfully init." << std::endl;
	running = true;
	return true;
}

//Application render loop: central handling
void Application::Run() {
	//GLFW window update every frame
	while (running && !window->ShouldClose()) {

		//Frame times
		float deltaTime = ComputeDeltaTime();
		frameTimingHistory.Push(
			deltaTime * 1000.0f, // CPU ms
			deltaTime * 1000.0f, // GPU placeholder
			deltaTime             // seconds
		);

		window->PollEvents();

		Input::Update();
		cameraController->Update(deltaTime);

		//UI update
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		uiSystem->BeginFrame();
		uiSystem->DrawFrame(*scene);
		uiSystem->EndFrame();

		ImGui::Render();

		//--------END UI--------------

		renderer->BeginFrame();
		renderer->Render(*scene,*camera);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		renderer->EndFrame();

		window->SwapBuffers();
	}
}

void Application::ShutDown() {

	//ENABLE LATER AFTER CONCERETE IMPLEMENTATIONS
	//unsubscribe all observers
	//lightingSystem->UnregisterObserver(shadowSystem.get());
}

//PRIMITIVES

PrimitiveHandle Application::CreatePlane(float size) {
	std::cout << "Attempting primitive factory from facade." << std::endl;
	auto p = PrimitiveFactory::CreatePlane(size);
	return scene->AddPrimitive(std::move(p));
}

PrimitiveHandle Application::CreateSphere(float radius, uint32_t stacks, uint32_t sectors) {
	std::cout << "Application facade attempting to create sphere." << std::endl;
	auto p = PrimitiveFactory::CreateSphere(radius,stacks,sectors);
	return scene->AddPrimitive(std::move(p));
}

PrimitiveHandle Application::CreateBox(float length, float width, float height) {
	std::cout << "Application facade attempting box." << std::endl;
	auto p = PrimitiveFactory::CreateBox(length, width, height);
	return scene->AddPrimitive(std::move(p));
}

PrimitiveHandle Application::CreateCone(float radius, float height, uint32_t sectors) {
	std::cout << "Application facade attempting cone." << std::endl;
	auto p = PrimitiveFactory::CreateCone(radius, height,sectors);
	return scene->AddPrimitive(std::move(p));
}

//LIGHTS
LightHandle Application::CreateDirectionalLight()
{
	DirectionalLight light; // default values
	return scene->AddDirectionalLight(light);
}

LightHandle Application::CreateSpotLight() {
	SpotLight light;
	return scene->AddSpotLight(light);
}

LightHandle Application::CreatePointLight() {
	PointLight light;
	return scene->AddpointLight(light);
}

//LATENCY
float Application::ComputeDeltaTime() {
	double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;
	return deltaTime;
}