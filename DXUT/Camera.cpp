#include "Camera.h"

Camera::Camera(const Window* window) : Movable(Position::Zero), _window(window) {
	UpdateAspect();
}

Camera::Camera(const Window* window,const Position & pos) : Movable(pos), _window(window) {
	UpdateAspect();
}

void Camera::LookAt(const Vector& pos){
	this->_pointOfView = pos;
}


void Camera::TranslateLookAt(const Vector& delta) {
	_pointOfView.TranslateTo(delta);
}


Position Camera::pointOfView()const{
	return this->_pointOfView;
}

void Camera::SetOrientation(const Vector& orientation){
	this->_orientation = orientation;
}
Vector Camera::orientation(){
	return this->_orientation;
}


void Camera::Draw(){
}

void Camera::Reset() {
	Position _pointOfView = Position::Zero;
	Vector _orientation = Vector::Up;
	this->RotateTo(Vector::Zero);
}


float Camera::frustumFov()const { return _fov; }
float Camera::frustumAspect()const{ return _aspect; }
float Camera::frustumNear()const{ return _near; }
float Camera::frustumFar()const{ return _far; }

void Camera::SetFrustumFov(float value) { _fov = value; }
void Camera::SetFrustumNear(float value){ _near = value; }
void Camera::SetFrustumFar(float value){ _far = value; }

void Camera::UpdateAspect() { _aspect = static_cast<float>(_window->Width() / (float)_window->Height()); }
