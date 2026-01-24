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

	//Lighting system based calls
	LightHandle AddLight(const Lightdata& dat);
	void RemoveLight(LightHandle id);
	void ModifyLight(LightHandle id, const Lightdata& dat);
private:
	~Application() = default; //default destructor compiler generated
	//std::unique_ptr<LightingSystem> lightingSystem;
	//std::unique_ptr<ShadowSystem> shadowSystem;

	std::unique_ptr<IWindow> window;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Scene> scene;
	bool running{ false };
};