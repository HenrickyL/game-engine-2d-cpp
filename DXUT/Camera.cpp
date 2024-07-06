#include "Camera.h"

Camera::Camera(const Graphics* graphic) : Movable(Position::Zero), _graphics(graphic) {
	UpdateAspect();
}

Camera::Camera(const Graphics* graphic,const Position & pos) : Movable(pos), _graphics(graphic) {
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
Vector Camera::orientation()const{
	return this->_orientation;
}

void Camera::SetDirection(const Vector& value) { _orientation = value; }
Vector Camera::direction()const { return _direction; }
Vector Camera::left()const { return _left; }

void Camera::Draw(){
}

void Camera::Reset() {
	Position _pointOfView = Position::Zero;
	Vector _orientation = Vector::Up;
	this->RotateTo(Vector::Zero);
}


float Camera::fov()const { return _fov; }
float Camera::aspect()const{ return _aspect; }
float Camera::zNear()const{ return _near; }
float Camera::zFar()const{ return _far; }

void Camera::SetFov(float value) { _fov = value; UpdateProjection(); }
void Camera::SetNear(float value){ _near = value;}
void Camera::SetFar(float value){ _far = value;}

void Camera::UpdateAspect() { _aspect = static_cast<float>(_graphics->Width() / (float)_graphics->Height()); }

void Camera::UpdateProjection() const {}
