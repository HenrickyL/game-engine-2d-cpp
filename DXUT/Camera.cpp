#include "Camera.h"

Camera::Camera(const Window* window) : Movable(Position::Zero), _window(window) {
}

Camera::Camera(const Window* window,const Position & pos) : Movable(pos), _window(window) {
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