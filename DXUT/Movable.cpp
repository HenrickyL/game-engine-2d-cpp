#include "Movable.h"

Movable::Movable(Position position, Vector speed) {
    this->_position = position;
    this->_anchor = position;
    this->_speed = speed;
    this->_magnitude = 0;
    this->_positionInitial = position;
}

Movable::~Movable() {}

void Movable::MoveTo(const Position& position) {
    this->_position.MoveTo(position);
}

void Movable::MoveTo(Position* position) {
    this->_position.MoveTo(position);
}

void Movable::TranslateTo(const Vector& delta) {
    this->_position.TranslateTo(delta);
}



Position Movable::position() const{
    return this->_position;
}
Position Movable::initialPosition() const{
    return this->_positionInitial;
}
float Movable::x() const{
    return this->_position.x();
}
float Movable::y() const{
    return this->_position.y();
}
float Movable::z() const{
    return this->_position.z();
}


float Movable::xRot() const {
    return this->_rotation.x();
}

float Movable::yRot() const {
    return this->_rotation.y();
}

float Movable::zRot() const {
    return this->_rotation.z();
}



Vector Movable::speed() const{
    return this->_speed;
}

double Movable::magnitude() const {
    return this->_magnitude;
}

Vector Movable::FinalSpeed() const{
    return this->_speed * this->_magnitude;
}
double Movable::rotateAngle() const{
    return this->_rotateRad * 180 / M_PI;
}
Position Movable::anchor() const{
    return this->_anchor;
}

Vector Movable::rotation() const {
    return this->_rotation;
}


void Movable::Speed(const Vector speed){
    this->_speed = speed;
}
void Movable::Magnitude(const double value){
    this->_magnitude = value;
}
void Movable::RotateAngle(const double angle){
    this->_rotateRad = angle * M_PI / 180;
}
void Movable::Anchor(Position pos){
    this->_anchor = pos;
}

void Movable::Rotation(const Vector& value) {
    this->_rotation = value;
}


void Movable::RotationZ(const float value) {
    this->_rotation.SetZ(value);
}

void Movable::RotationX(const float value) {
    this->_rotation.SetX(value);
}

void Movable::RotationY(const float value) {
    this->_rotation.SetY(value);
}

