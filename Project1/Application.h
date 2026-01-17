#pragma once
#include"LightingSystem.h"
#include"LightData.h"
#include<memory>

//APPLICATION FACADE CONNECTS ALL SUBSYSTEMS
class Application {
public:
	//Singleton constructor
	static Application& Instance(){
		static Application instance;
		return instance;
	}

	//Lighting system based calls
	LightHandle AddLight(const Lightdata& dat);
	void RemoveLight(LightHandle id);
	void ModifyLight(LightHandle id, const Lightdata& dat);
private:
	~Application() = default; //default destructor compiler generated
	std::unique_ptr<LightingSystem> lightingSystem;
};