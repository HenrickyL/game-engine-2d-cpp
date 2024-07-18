#include "GLGraphics.h"
#include <stdexcept>

GLGraphics::GLGraphics(GLWindow* window) {
    this->_window = window;
    _currentFPS = FPS_MAX;
}

GLGraphics::~GLGraphics() {}

bool GLGraphics::Initialize() {
    // Inicialização do GLEW para carregar as funções do OpenGL
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW.");
        //MessageBox(nullptr, reinterpret_cast<LPCSTR>(glewGetErrorString(glewError)), "Erro ao inicializar GLEW", MB_OK);
        return false;
    }

    _viewportWidth = float(_window->Width());
    _viewportHeight = float(_window->Height());
    glViewport(0, 0, _viewportWidth, _viewportHeight); // Configura a viewport

    // Configuração do OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo preta
    
    setupPerspectiveContext();

    //// Configurações adicionais do OpenGL
    glEnable(GL_DEPTH_TEST); // Ativa o teste de profundidade
    //enable opacity
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    //antialising GL_MULTISAMPLE
    glEnable(GL_LINE_SMOOTH);
    /*glEnable(GL_MULTISAMPLE);
    glSampleCoverage(1.0f, GL_FALSE);*/

    //VSync(_onVSync);
    ///TODO: Analisar melhor 
    glfwSwapInterval(1);
    return true; // Inicialização bem-sucedida
}


void GLGraphics::setupPerspectiveContext() const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (_type == T_3D) {
        set3DRenderContext();
    }
    else {
        //set2DRenderContext();
    }
    glMatrixMode(GL_MODELVIEW);
}


void GLGraphics::VSync(bool state) {
    _onVSync = state;
    if (_onVSync) {
        glfwSwapInterval(1); // Ativa o VSync
    }
    else {
        glfwSwapInterval(0); // Desativa o VSync
    }
}

void GLGraphics::Clear() {
    _window->Clear();
}

void GLGraphics::Present() {
    glfwSwapBuffers(dynamic_cast<GLWindow*>(_window)->GetWindow()); // Troca os buffers de framebuffer
}


void GLGraphics::set3DRenderContext() const {
    // Configura o contexto de renderização para 3D
    _aspect = (double)_viewportWidth / (double)_viewportHeight;
    gluPerspective(_fovy, _aspect, _zNear, _zFar);
}

void GLGraphics::set2DRenderContext() const {
    // Configura o contexto de renderização para 2D
    gluOrtho2D(0, _viewportWidth, 0, _viewportHeight);
}