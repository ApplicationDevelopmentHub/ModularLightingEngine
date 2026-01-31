#pragma once
#include"LightingSystem.h"
#include"LightData.h"
#include"ShadowSystem.h"
#include"IWindow.h"
#include"GLFWWindow.h"
#include<memory>
#include"PrimitiveHandle.h"
#include"Scene.h"
#include"Renderer.h"
#include"OpenGLRenderer.h"
#include"PrimitiveFactory.h"
#include"Camera.h"
#include"CameraController.h"
#include"UISystem.h"
#include<imgui.h>
#include<ImGui/imgui_impl_opengl3.h>
#include<ImGui/imgui_impl_glfw.h>
#include"UIInspectorPanel.h"
#include"UIHierarchyPanel.h"
#include"UIMenuPanel.h"
#include"UILatencyPanel.h"
#include"FrameTimingHistory.h"

//APPLICATION FACADE CONNECTS ALL SUBSYSTEMS
class Application {
public:
	//Singleton constructor
	static Application& Instance(){
		static Application instance;
		return instance;
	}

	//Init Application:create objects, assign references, define subsystems
	bool Init(); //returns false if some component fails to init
	void Run(); //Render loop
	void ShutDown();

	//Primitives
	PrimitiveHandle CreatePlane(float size);
	PrimitiveHandle CreateSphere(float radius, uint32_t stacks, uint32_t sectors);
	PrimitiveHandle CreateBox(float length, float width, float height);
	PrimitiveHandle CreateCone(float radius, float height, uint32_t sectors);

	//Lighting system based calls
	LightHandle AddLight(const Lightdata& dat);
	void RemoveLight(LightHandle id);
	void ModifyLight(LightHandle id, const Lightdata& dat);
private:
	~Application() = default; //default destructor compiler generated
	//std::unique_ptr<LightingSystem> lightingSystem;
	//std::unique_ptr<ShadowSystem> shadowSystem;

	float ComputeDeltaTime();
	double lastTime = 0.0f;

	std::unique_ptr<IWindow> window;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<CameraController> cameraController;
	std::unique_ptr<UISystem> uiSystem;

	FrameTimingHistory frameTimingHistory;
	bool running{ false };
};