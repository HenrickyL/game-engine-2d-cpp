#include "GLCamera.h"

GLCamera::GLCamera(const Window* window) : Camera(window) {}

GLCamera::GLCamera(const Window* window, const Position& pos): Camera(window, pos) {}


void GLCamera::Update() {
	gluLookAt(
		_position.x(), _position.y(), _position.z(),
		_pointOfView.x(), _pointOfView.y(), _pointOfView.z(),
		_orientation.x(), _orientation.y(), _orientation.z());
}