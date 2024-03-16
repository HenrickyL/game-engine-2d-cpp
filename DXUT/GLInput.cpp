#include "GLInput.h"


GLInput::GLInput() {
    //glfwSetCursorPosCallback(GLWindow::window, cursor_position_callback);
}

void GLInput::InputKeysProc(GLFWwindow* window, int key, int scancode, int action, int mods){
    // Ignore as teclas desconhecidas
    if (key == GLFW_KEY_UNKNOWN) return;

    // Certifique-se de que a chave está dentro do intervalo do array
    if (key >= 0 && key < 256) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

void GLInput::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    mousePosition->SetX(xpos);
    mousePosition->SetY(ypos);
}
