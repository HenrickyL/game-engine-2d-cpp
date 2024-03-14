#include "GLInput.h"

GLKeyCallbackType GLInput::keyCallbackPtr = GLWindow::GlProcCallback;


InputKeys GLInput::convertGLFWKey(int glfwKey) {
    switch (glfwKey) {
    case GLFW_KEY_SPACE: return SPACE;
    case GLFW_KEY_A: return KEY_A;
    case GLFW_KEY_B: return KEY_B;
        //others
    default: return UNKNOWN;
    }
}

void GLInput::InputKeysProc(GLFWwindow* window, int key, int scancode, int action, int mods){


}