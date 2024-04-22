#include "Graphics.h"


void Graphics::SetViewportWidth(float width) {
    this->viewportWidth = width;
}

void Graphics::SetViewportHeight(float height) {
    this->viewportHeight = height;
}

float Graphics::ViewportWidth() const {
    return this->viewportWidth;
}

float Graphics::ViewportHeight() const {
    return this->viewportHeight;
}

void Graphics::SetFPS(FPSType fps) {
    currentFPS = fps;
}

FPSType Graphics::FPS() const {
    return currentFPS;
}