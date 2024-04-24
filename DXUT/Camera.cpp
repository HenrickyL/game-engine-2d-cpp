#include "Camera.h"

Camera::Camera() : Movable(Position::Zero) {
}

Camera::Camera(const Position & pos) : Movable(pos) {
}

void Camera::LookAt(const Position& pos){
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