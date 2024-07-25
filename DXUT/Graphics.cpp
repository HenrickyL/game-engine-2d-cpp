#include "Graphics.h"


double Graphics::_fovy = 45.0f; //angle degree
double Graphics::_aspect = 0; //proporsion
double Graphics::_zNear = 0.1f;
double Graphics::_zFar = 500.0f;

void Graphics::SetViewportWidth(float width) {
    this->_viewportWidth = width;
}

void Graphics::SetViewportHeight(float height) {
    this->_viewportHeight = height;
}

float Graphics::ViewportWidth() const {
    return this->_viewportWidth;
}

float Graphics::ViewportHeight() const {
    return this->_viewportHeight;
}

void Graphics::SetFPS(FPSType fps) {
    _currentFPS = fps;
}

FPSType Graphics::FPS() const {
    return _currentFPS;
}


float Graphics::Width() const {
    return _window->Width();
}
float Graphics::Height() const {
    return _window->Height();
}