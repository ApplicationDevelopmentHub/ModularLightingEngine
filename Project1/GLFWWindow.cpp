#include"GLFWWindow.h"
#include<GLFW/glfw3.h>
#include<iostream>

using namespace std;

GLFWWindow::GLFWWindow():window(nullptr) {}

//things to shut down in glfw systematically
GLFWWindow::~GLFWWindow() {
	cout << "Calling GLFW Window destructor" << endl;
	if (window) {
		glfwDestroyWindow(static_cast<GLFWwindow*>(window));
	}
	glfwTerminate();
}

bool GLFWWindow::Create(int width, int height, const char* title) {
	if (!glfwInit()) {
		cout << "GLFW init failed" << endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* glfw_window = glfwCreateWindow(width,height,title,nullptr,nullptr);

	//if window failes to create, return
	if (!glfw_window) {
		cout << "glfw window failed." << endl;
		glfwTerminate();
		return false;
	}

	window = glfw_window; //assign as the current handle
	glfwMakeContextCurrent(glfw_window); //This window the one being used by OpenGL currenly
	glViewport(0, 0, width, height);
	return true;
}

void GLFWWindow::PollEvents() {
	glfwPollEvents();
}

void GLFWWindow::SwapBuffers() {
	glfwSwapBuffers(static_cast<GLFWwindow*>(window));
}

bool GLFWWindow::ShouldClose() {
	return glfwWindowShouldClose(static_cast<GLFWwindow*>(window));
}
void* GLFWWindow::GetNativeHandle() const {
	return window;
}