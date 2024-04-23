#include "GLGraphics.h"


GLGraphics::GLGraphics(GLWindow* window) {
    this->_window = window;
    _currentFPS = FPS_MAX;
    _viewportWidth = float(window->Width());
    _viewportHeight = float(window->Height());
}

GLGraphics::~GLGraphics() {}

bool GLGraphics::Initialize() {
    // Inicialização do GLEW para carregar as funções do OpenGL
    /*glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        MessageBox(nullptr, reinterpret_cast<LPCSTR>(glewGetErrorString(glewError)), "Erro ao inicializar GLEW", MB_OK);
        return false;
    }*/

    // Configuração do OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo preta
    glEnable(GL_DEPTH_TEST); // Ativa o teste de profundidade
    glViewport(0, 0, _window->Width(), _window->Height()); // Configura a viewport

    if (_type == T_3D) {
        set3DRenderContext();
    }
    else {
        set2DRenderContext();
    }

    VSync(_onVSync);
    return true; // Inicialização bem-sucedida
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, _aspect, _zNear, _zFar);
    glMatrixMode(GL_MODELVIEW);
}

void GLGraphics::set2DRenderContext() const {
    // Configura o contexto de renderização para 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, _viewportWidth, 0, _viewportHeight);
    glMatrixMode(GL_MODELVIEW);
}