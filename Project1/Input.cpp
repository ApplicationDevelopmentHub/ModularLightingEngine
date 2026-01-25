#include "Input.h"
#include <cstring>

GLFWwindow* Input::s_window = nullptr;
bool Input::s_keys[1024] = {};
bool Input::s_prevKeys[1024] = {};

void Input::Init(GLFWwindow* window) {
    s_window = window;
    std::memset(s_keys, 0, sizeof(s_keys));
    std::memset(s_prevKeys, 0, sizeof(s_prevKeys));
}

void Input::Update() {
    // Store previous frame state
    std::memcpy(s_prevKeys, s_keys, sizeof(s_keys));

    // Poll all keys we care about
    for (int key = 0; key < 1024; ++key) {
        s_keys[key] =
            glfwGetKey(s_window, key) == GLFW_PRESS;
    }
}

bool Input::IsKeyDown(int key) {
    return s_keys[key];
}

bool Input::IsKeyPressed(int key) {
    return s_keys[key] && !s_prevKeys[key];
}

bool Input::IsKeyReleased(int key) {
    return !s_keys[key] && s_prevKeys[key];
}
