#include "GLInput.h"
#include "GLKeyMap.h"
#include <cstdlib>
#include <chrono>
#include <iostream>
using TimeType = std::chrono::steady_clock::time_point;




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

void GLInput::InputMouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    lastMouseClick.SetX(mouseClick.x());
    lastMouseClick.SetY(mouseClick.y());
    
    onClick = action != GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT;

    glfwGetCursorPos(window, &xpos, &ypos);
    mouseClick.SetX(xpos);
    mouseClick.SetY(ypos);
}

void GLInput::InputMousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
    mousePosition.SetX(xpos);
    mousePosition.SetY(ypos);

    if (onClick) {
        //drag
        short diffX = abs(mouseClick.x() - mousePosition.x());
        short diffY = abs(mouseClick.y() - mousePosition.y());
       
        if (diffX > dragOffset) {
            drag.SetX(diffX);
        }

        if (diffY > dragOffset) {
            drag.SetY(diffY);
        }
    }
    else {
        drag.SetX(0);
        drag.SetY(0);
    }
}

void GLInput::InputMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    static TimeType _LAST_TIME_ = std::chrono::steady_clock::now();

    lastMouseWheel = mouseWheel;
    mouseWheel += (short)yoffset;

    auto timeNow = std::chrono::steady_clock::now();
    auto diff = timeNow - _LAST_TIME_;
    auto diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

    if (diff_ms.count() > timeOffset) {
        mouseWheel = (short)yoffset;
        lastMouseWheel = mouseWheel;
    }
    _LAST_TIME_ = timeNow;
}


InputKeys GLInput::GetKey(int key) {
    auto res = GLKeyMap[key];
    return res;
}
