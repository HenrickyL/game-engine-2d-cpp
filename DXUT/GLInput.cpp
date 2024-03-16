#include "GLInput.h"
#include "GLKeyMap.h"

void GLInput::InputKeysCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // Ignore as teclas desconhecidas
    if (key == GLFW_KEY_UNKNOWN) return;

    // Certifique-se de que a chave está dentro do intervalo do array
    InputKeys keyCode = GetKey(key);
    //if (key >= 0 && key < 256) {
        if (action == GLFW_PRESS) {
            keys[keyCode] = true;
        }
        else if (action == GLFW_RELEASE) {
            keys[keyCode] = false;
        }
    //}
}

/*
* action
    GLFW_PRESS (indicando que o botão do mouse foi pressionado)
    GLFW_RELEASE (indicando que o botão do mouse foi liberado)
    GLFW_REPEAT (indicando que o botão do mouse foi mantido pressionado)
* button:
    GLFW_MOUSE_BUTTON_LEFT
    GLFW_MOUSE_BUTTON_RIGHT
    GLFW_MOUSE_BUTTON_MIDDLE
* mods:
    GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, e GLFW_MOD_SUPER
*/

void GLInput::InputMousePositionCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mousePosition.SetX(xpos);
    mousePosition.SetY(ypos);

    if (action == GLFW_PRESS && GLFW_MOUSE_BUTTON_LEFT) {
        mouseClick.SetX(xpos);
        mouseClick.SetY(ypos);
    }
}


InputKeys GLInput::GetKey(int key) {
    auto res = GLKeyMap[key];
    return res;
}
