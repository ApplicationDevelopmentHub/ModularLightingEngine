#pragma once
#include <GLFW/glfw3.h>

class Input {
public:
    // Must be called once after window creation
    static void Init(GLFWwindow* window);

    // Keyboard
    static bool IsKeyDown(int key);
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    // Per-frame update (optional but important for pressed/released)
    static void Update();

private:
    static GLFWwindow* s_window;

    static bool s_keys[1024];
    static bool s_prevKeys[1024];
};
