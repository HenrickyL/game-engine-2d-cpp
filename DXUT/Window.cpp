#include "Window.h"


void Window::UpdateAspect() { _aspect = static_cast<float>(_width/ _height); }

double Window::fovy()const { return _fovy; };
double Window::aspect()const { return _aspect; }
double Window::zNear() const { return _zNear; }
double Window::zFar()const { return _zFar; }

void Window::SetFovy(double value) { _fovy = value; }
void Window::SetNear(double value){ _zNear = value; }
void Window::SetFar(double value){ _zFar = value; }


HWND Window::Id() const { return 0; }
void Window::isResizeable(bool value) { this->_allowResize = value; }

int Window::Width() const { return _width; }
int Window::Height() const { return _height; }
WindowModes Window::Mode() const { return _mode; }
std::string Window::Title() const { return _title; }
Position Window::Center() const { return Position(_width / 2, _height / 2); }
void Window::SetColor(Color color) { _color = color; }

void Window::SetCursorDisable(bool value) { _isCursorDisable = value; }
bool Window::isCursorDisable()const { return _isCursorDisable; }


void Window::Size(int width, int height) {
	_width = width;
	_height = height;
	UpdateAspect();
}

