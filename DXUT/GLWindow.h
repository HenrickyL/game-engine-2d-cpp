// GLWindow.h
#ifndef DXUT_GLFWWINDOW_H
#define DXUT_GLFWWINDOW_H


#include "Window.h"
#include <GLFW/glfw3.h>


class GLFWWindow : public Window {
private:
    GLFWwindow* window;// Ponteiro para a janela GLFW

    // Funções estáticas para manipulação de eventos GLFW
    static void onResize(GLFWwindow* window, int width, int height);
    static void onFocus(GLFWwindow* window, int focused);

public:
    GLFWWindow(); // Construtor
    ~GLFWWindow(); // Destrutor

};

#endif