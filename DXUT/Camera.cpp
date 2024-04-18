#include "Camera.h"

Camera::Camera(): Movable(Position::Zero) {
}


void Camera::LookAt(const Position& pos){
	this->_pointOfView = pos;
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

void Camera::Update(){
}
void Camera::Draw(){
}