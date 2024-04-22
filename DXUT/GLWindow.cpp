#include "GLWindow.h"
#include "GLInput.h"
// GLWindow.cpp

GLFWwindow* GLWindow::window = nullptr;// Ponteiro para a janela GLFW
GLdouble GLWindow::_fovy = 45.0f ; //angle degree
double GLWindow::_aspect = 0; //proporsion
GLdouble GLWindow::_zNear = 0.1f;
GLdouble GLWindow::_zFar = 500.0f;

GLWindow::GLWindow(){}

GLWindow::~GLWindow() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}


void GLWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    glfwSetWindowSize(window, width, height); 
    // Calcula a proporção da janela
    _aspect = (double)width / (double)height;

    // Define a viewport para corresponder ao novo tamanho da janela
    glViewport(0, 0, width, height);

    // Configura a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Ajusta a matriz de projeção para manter a proporção da cena
    gluPerspective(_fovy, _aspect, _zNear, _zFar);

    glMatrixMode(GL_MODELVIEW);
}

void GLWindow::setupWindowCallbacks() {
    if (window) {
        glfwSetKeyCallback(window, GLInput::InputKeysCallback);
        glfwSetMouseButtonCallback(window, GLInput::InputMouseClickCallback);
        glfwSetCursorPosCallback(window, GLInput::InputMousePositionCallback);
        glfwSetScrollCallback(window, GLInput::InputMouseScrollCallback);
        // Verifica se o redimensionamento da janela é permitido - use null para não fazer ajustes
        glfwSetWindowSizeCallback(window, GLWindow::windowSizeCallback);

    }
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
    windowSizeCallback(window, _width, _height);
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


void GLWindow::HideCursor(bool hide) {
    // Implemente lógica para ocultar o cursor da janela com GLFW
}

void GLWindow::Close() {
    //glfwSetWindowShouldClose(GLWindow::window, GLFW_TRUE);
    glfwTerminate();
}

GLFWwindow* GLWindow::GetWindow()const {
    return window;
}

double GLWindow::Aspect() const {
    return _aspect;
}



void GLWindow::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_color.r(), _color.g(), _color.b(), _color.alpha());
}

bool GLWindow::Create() {
    // Inicialize GLFW
    if (!glfwInit()) {
        return false;
    }
    isResizeable(_allowResize);
    // Crie uma janela GLFW
    window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    onWindowCreate();
    setupWindowCallbacks();

    // Tornar o contexto da janela atual - mudar se for trabalhar com mais janelas
    glfwMakeContextCurrent(window);
    Size(_width, _height);
    //// Configurações adicionais do OpenGL
    glEnable(GL_DEPTH_TEST);

    _onCreate = true;
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
    return glfwWindowShouldClose(GLWindow::window);
}
void GLWindow::SwapBuffers() const {
    glfwSwapBuffers(GLWindow::window);
}
 void GLWindow::PollEvents() const {
    glfwPollEvents();
}

void GLWindow::isResizeable(bool value) {
    if(_onCreate) MessageBox(nullptr, "You cannot set this method 'isResizeable' after the window has been created.", "Error", MB_OK | MB_ICONERROR);
    _allowResize = value;
    glfwWindowHint(GLFW_RESIZABLE, _allowResize ? GLFW_TRUE : GLFW_FALSE);
}




void GLWindow::InFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela entra em foco com GLFW
}

void GLWindow::LostFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela perde o foco com GLFW
}
