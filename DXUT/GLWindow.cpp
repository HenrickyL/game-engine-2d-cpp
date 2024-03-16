#include "GLWindow.h"
#include "GLInput.h"
// GLWindow.cpp

GLFWwindow* GLWindow::window = nullptr;// Ponteiro para a janela GLFW


GLWindow::GLWindow(){}

GLWindow::~GLWindow() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void GLWindow::setupWindowInputCallback() {
    if (window) {
        glfwSetKeyCallback(window, GLInput::InputKeysCallback);
        glfwSetMouseButtonCallback(window, GLInput::InputMouseClickCallback);
        glfwSetCursorPosCallback(window, GLInput::InputMousePositionCallback);
        glfwSetScrollCallback(window, GLInput::InputMouseScrollCallback);
    }
}



int GLWindow::Width() const {
    return _width;
}

int GLWindow::Height() const{
    return _height;
}

WindowModes GLWindow::Mode() const {
    return _mode;
}

Position GLWindow::Center() const {
    // Implemente lógica para obter o centro da janela com GLFW
    return Position(); // Retorno padrão
}

std::string GLWindow::Title() const {
    return _title;
}

Color GLWindow::GetColor() const {
    // Implemente lógica para obter a cor de fundo da janela com GLFW
    return _color; // Cor padrão
}

void GLWindow::Icon(const uint icon) {
    // Implemente lógica para definir o ícone da janela com GLFW
}

void GLWindow::Cursor(const uint cursor) {
    // Implemente lógica para definir o cursor da janela com GLFW
}

void GLWindow::Title(const std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void GLWindow::Size(int width, int height) {
    glfwSetWindowSize(window, width, height);
    _width = width;
    _height = height;
}

void GLWindow::Mode(WindowModes mode) {
    switch (mode) {
        case WINDOWED:
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE); // Define como janela decorada (com borda)
            glfwSetWindowMonitor(window, nullptr, _windowPosX, _windowPosY, _width, _height, GLFW_DONT_CARE); // Configura como janela
            break;
        case FULLSCREEN:
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE); // Define como janela sem decoração (sem borda)
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, _width, _height, GLFW_DONT_CARE); // Configura como tela cheia
            break;
        case BORDERLESS:
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE); // Define como janela sem decoração (sem borda)
            glfwSetWindowMonitor(window, nullptr, _windowPosX, _windowPosY, _width, _height, GLFW_DONT_CARE); // Configura como janela sem borda
            break;
     }
}

void GLWindow::SetColor(Color color) {
    onWindowCreate("GLFW window was not created");
    // Define a cor de fundo da janela
    glClearColor(color.r(), color.g(), color.b(), color.alpha());
}

void GLWindow::HideCursor(bool hide) {
    // Implemente lógica para ocultar o cursor da janela com GLFW
}

void GLWindow::Close() {
    glfwTerminate();
}

GLFWwindow* GLWindow::GetWindow()const {
    return window;
}


void GLWindow::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

bool GLWindow::Create() {
    // Inicialize GLFW
    if (!glfwInit()) {
        return false;
    }

    // Crie uma janela GLFW
    window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    onWindowCreate();
    setupWindowInputCallback();

    // Tornar o contexto da janela atual - mudar se for trabalhar com mais janelas
    glfwMakeContextCurrent(window);

    //// Configurações adicionais do OpenGL
    //glEnable(GL_DEPTH_TEST);

    return true;
}


bool GLWindow::onWindowCreate(const string message) const {
    if (!window) {
        // Se a criação da janela falhar, exibir uma mensagem de erro e encerrar
        MessageBox(nullptr, message.c_str(),"Error", MB_OK | MB_ICONERROR);
        glfwTerminate();
        return false;
    }
}


bool GLWindow::ShouldClose() const {
    return glfwWindowShouldClose(window);
}
void GLWindow::SwapBuffers() const {
    glfwSwapBuffers(window);
}



void GLWindow::InFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela entra em foco com GLFW
}

void GLWindow::LostFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela perde o foco com GLFW
}
