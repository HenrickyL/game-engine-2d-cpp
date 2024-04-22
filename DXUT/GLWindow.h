// GLWindow.h
#ifndef DXUT_GLFWWINDOW_H
#define DXUT_GLFWWINDOW_H


#include "Window.h"
#include <GLFW/glfw3.h>
#include <gl/GLU.h>


class GLWindow : public Window {
private:
    static GLFWwindow* window;// Ponteiro para a janela GLFW

    //perspective
    static GLdouble _fovy; //angle degree
    static double _aspect; //proporsion
    static GLdouble _zNear ; 
    static GLdouble _zFar;

    // Funções estáticas para manipulação de eventos GLFW
    static void onResize(GLFWwindow* window, int width, int height);
    static void onFocus(GLFWwindow* window, int focused);

    bool onWindowCreate(const string message = "Failed to create GLFW window") const;
    void setupWindowCallbacks();
    static void windowSizeCallback(GLFWwindow* window, int width, int height);

public:
    GLWindow(); // Construtor
    ~GLWindow(); // Destrutor

    // Overrides dos métodos da classe Window
    Color GetColor() const override;
    void Icon(const uint icon) override;
    void Cursor(const uint cursor) override;
    void Title(const std::string title) override;
    void Size(int width, int height) override;
    void Mode(WindowModes mode) override;
    void HideCursor(bool hide) override;
    void InFocus(void(*func)()) override;
    void LostFocus(void(*func)()) override;
    void isResizeable(bool value) override;
    bool ShouldClose() const override;
    GLFWwindow* GetWindow()const;
    double Aspect() const;
    void Close() override;
    void Clear() override;
    bool Create() override;
    void SwapBuffers() const;
    void PollEvents() const override;


    //// tratamento de eventos do Windows
    //static void GlProcCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif