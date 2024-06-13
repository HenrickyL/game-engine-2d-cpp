#include "GLWindow.h"
#include "GLInput.h"
#include <stdexcept>

// GLWindow.cpp

GLFWwindow* GLWindow::window = nullptr;// Ponteiro para a janela GLFW
GLdouble GLWindow::_fovy = 45.0f ; //angle degree
double GLWindow::_aspect = 0; //proporsion
GLdouble GLWindow::_zNear = 0.1f;
GLdouble GLWindow::_zFar = 500.0f;

GLWindow::GLWindow(){
}

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

void GLWindow::SetTitle(const std::string title) {
    this->_title = title;
    glfwSetWindowTitle(window, this->_title.c_str());
    resetApplyUpdate();
}

void GLWindow::Size(int width, int height) {
    glfwSetWindowSize(window, width, height);
    _width = width;
    _height = height;
    windowSizeCallback(window, _width, _height);
}

void GLWindow::Mode(WindowModes mode) {
    _mode = mode;
    
}


void GLWindow::HideCursor(bool hide) {
    // Implemente lógica para ocultar o cursor da janela com GLFW
}

GLFWwindow* GLWindow::GetWindow()const {
    return window;
}

double GLWindow::Aspect() const {
    return _aspect;
}



void GLWindow::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_color.r(), _color.g(), _color.b(), _color.a());
    glLineWidth(1.0f);
    glPointSize(1.0f);
}

GLFWwindow* GLWindow::CreateWindowByMode() {
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* modeInfo = nullptr;

    monitor = glfwGetPrimaryMonitor();
    modeInfo = glfwGetVideoMode(monitor);
    if (_mode == FULLSCREEN) {
        _width = modeInfo->width;
        _height = modeInfo->height;
    }

    GLFWwindow* window = nullptr;
    if (_mode == FULLSCREEN) {
        window = glfwCreateWindow(_width,_height, _title.c_str(), monitor, nullptr);
    }
    else {
        window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_mode == BORDERLESS) {
            glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
            const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowPos(window, 0, 0);
            glfwSetWindowSize(window, videoMode->width, videoMode->height);
        }
        // Centralizar a janela
        int xpos = (modeInfo->width - _width) / 2;
        int ypos = (modeInfo->height - _height) / 2;
        glfwSetWindowPos(window, xpos, ypos);
    }

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }

    return window;
}


bool GLWindow::Create() {
    // Inicialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
        return false;
    }
    isResizeable(_allowResize);
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
    // Crie uma janela GLFW
    window = CreateWindowByMode();
    onWindowCreate();
    setupWindowCallbacks();

    // Tornar o contexto da janela atual - mudar se for trabalhar com mais janelas
    glfwMakeContextCurrent(window);
    Size(_width, _height);
    //// Configurações adicionais do OpenGL
    glEnable(GL_DEPTH_TEST);
    //enable opacity
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    this->SetCursorDisable(isCursorDisable());

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

void GLWindow::Close() {
    glfwSetWindowShouldClose(GLWindow::window, GLFW_TRUE);
    //glfwTerminate();
}

bool GLWindow::ShouldClose() const {
    return glfwWindowShouldClose(GLWindow::window);
}
void GLWindow::SwapBuffers() const {
    glfwSwapBuffers(GLWindow::window);
}
 void GLWindow::PollEvents() {
    glfwPollEvents();
    updateValues();
}

void GLWindow::isResizeable(bool value) {
    if(_onCreate) MessageBox(nullptr, "You cannot set this method 'isResizeable' after the window has been created.", "Error", MB_OK | MB_ICONERROR);
    _allowResize = value;
    // Configure o GLFW
    glfwWindowHint(GLFW_RESIZABLE, _allowResize ? GLFW_TRUE : GLFW_FALSE);
}


void GLWindow::SetCursorDisable(bool value) {
    Window::SetCursorDisable(value);
    glfwSetInputMode(GLWindow::window, GLFW_CURSOR, isCursorDisable() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void GLWindow::updateValues() {
    if (_onUpdate && !_onApply) {
        SetTitle(this->_title);
        _onUpdate = false;
        _onApply = true;
    }
}

void GLWindow::resetApplyUpdate() {
    _onApply = false;
    _onUpdate = true;
}



void GLWindow::InFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela entra em foco com GLFW
}

void GLWindow::LostFocus(void(*func)()) {
    // Implemente lógica para definir a função a ser chamada quando a janela perde o foco com GLFW
}
