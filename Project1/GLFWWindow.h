#pragma once
#include"IWindow.h"

class GLFWWindow :public IWindow {
public:
	GLFWWindow();
	~GLFWWindow() override;

	bool Create(int width, int height, const char* title);
	void PollEvents();
	void SwapBuffers();
	bool ShouldClose();
	void* GetNativeHandle() const;
private:
	void* window;
};
