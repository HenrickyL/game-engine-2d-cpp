// GLWindow.h
#ifndef DXUT_GLFWWINDOW_H
#define DXUT_GLFWWINDOW_H


#include "Window.h"
#include <GLFW/glfw3.h>


class GLWindow : public Window {
private:
    static GLFWwindow* window;// Ponteiro para a janela GLFW

    // Funções estáticas para manipulação de eventos GLFW
    static void onResize(GLFWwindow* window, int width, int height);
    static void onFocus(GLFWwindow* window, int focused);

    bool onWindowCreate(const string message = "Failed to create GLFW window") const;

public:
    GLWindow(); // Construtor
    ~GLWindow(); // Destrutor

    // Overrides dos métodos da classe Window
    int Width() const override;
    int Height() const override;
    WindowModes Mode() const override;
    Position Center() const override;
    std::string Title() const override;
    Color GetColor() const override;
    void Icon(const uint icon) override;
    void Cursor(const uint cursor) override;
    void Title(const std::string title) override;
    void Size(int width, int height) override;
    void Mode(WindowModes mode) override;
    void SetColor(Color color) override;
    void HideCursor(bool hide) override;
    void InFocus(void(*func)()) override;
    void LostFocus(void(*func)()) override;

    GLFWwindow* GetWindow()const;
    void Close() override;
    void Clear() override;
    bool Create() override;
    bool ShouldClose() const;
    void SwapBuffers() const;

    //// tratamento de eventos do Windows
    //static void GlProcCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif