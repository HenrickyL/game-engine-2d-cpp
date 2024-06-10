#include "GLCamera.h"

GLCamera::GLCamera(const Window* window) : Camera(window) {}

GLCamera::GLCamera(const Window* window, const Position& pos): Camera(window, pos) {}


void GLCamera::Update() {
	_pointOfView = position() + _direction;

	gluLookAt(
		position().x(), position().y(), position().z(),
		_pointOfView.x(), _pointOfView.y(), _pointOfView.z(),
		_orientation.x(), _orientation.y(), _orientation.z());
}


void GLCamera::LookAt(const Vector& pos) {
	//_direction.TranslateTo(pos);
	//_left.TranslateTo(pos);

}
