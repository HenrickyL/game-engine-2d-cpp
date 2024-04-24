#include "GLCamera.h"

GLCamera::GLCamera() : Camera() {}

GLCamera::GLCamera(const Position& pos): Camera(pos) {}


void GLCamera::Update() {
	gluLookAt(
		_position.x(), _position.y(), _position.z(),
		_pointOfView.x(), _pointOfView.y(), _pointOfView.z(),
		_orientation.x(), _orientation.y(), _orientation.z());
}