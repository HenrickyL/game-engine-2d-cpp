#include "Movable.h"



Movable::Movable() {}

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
    this->SetDirt();
}

void Movable::MoveTo(Position* position) {
    this->_position.MoveTo(position);
    this->SetDirt();
}

void Movable::TranslateTo(const Vector& delta) {
    this->_position.TranslateTo(delta);
    this->SetDirt();
}



const Position Movable::position() const{
    return this->_position;
}
const Position Movable::initialPosition() const{
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
    return this->_rotations.x();
}

float Movable::yRot() const {
    return this->_rotations.y();
}

float Movable::zRot() const {
    return this->_rotations.z();
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

const Position Movable::anchor() const{
    return this->_anchor;
}

Vector Movable::rotations() const {
    return this->_rotations;
}


void Movable::SetSpeed(const Vector speed){
    this->_speed = speed;
    this->SetDirt();
}
void Movable::SetRotation(const Vector speed) {
    this->_rotations = speed;
    this->SetDirt();
}

void Movable::SetPosition(const Position value) {
    this->_position = value;
    this->SetDirt();
}
void Movable::SetMagnitude(const double value){
    this->_magnitude = value;
    this->SetDirt();
}

void Movable::SetAnchor(Position pos){
    this->_anchor = pos;
    this->SetDirt();
}

void Movable::RotateTo(const Vector& value) {
    this->_rotations = value;
    this->SetDirt();
}

void Movable::RotateBy(const Vector& delta) {
    this->_rotations.TranslateTo(delta);
    this->SetDirt();
}


void Movable::SetRotationZ(const float value) {
    this->_rotations.SetZ(value);
    this->SetDirt();
}

void Movable::SetRotationX(const float value) {
    this->_rotations.SetX(value);
    this->SetDirt();
}

void Movable::SetRotationY(const float value) {
    this->_rotations.SetY(value);
    this->SetDirt();
}

