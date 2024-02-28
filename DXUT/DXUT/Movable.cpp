#include "Movable.h"

Movable::Movable(Position position, Vector speed) {
    this->_position = position;
    this->_anchor = position;
    this->_speed = speed;
    this->_positionInitial = position;
}

Movable::~Movable() {}

void Movable::MoveTo(Position position){
    this->_position.MoveTo(position);

}

void Movable::TranslateTo(Vector delta) {
    this->_position.Translate(delta);
}



Position Movable::position() const{
    return this->_position;
}
Position Movable::initialPosition() const{
    return this->_positionInitial;
}
int Movable::x() const{
    return this->_position.X();
}
int Movable::y() const{
    return this->_position.Y();

}
int Movable::z() const{
    return this->_position.Z();

}
Vector Movable::speed() const{
    return this->_speed;
}
Vector Movable::FinalSpeed() const{
    return this->_speed * this->_speedMag;
}
double Movable::rotateAngle() const{
    return this->_rotateRad * 180 / M_PI;
}
Position Movable::anchor() const{
    return this->_anchor;
}

void Movable::Speed(const Vector speed){
    this->_speed = speed;
}
void Movable::SpeedMag(const double value){
    this->_speedMag = value;
}
void Movable::RotateAngle(const int angle){
    this->_rotateRad = angle * M_PI / 180;
}
void Movable::Anchor(Position pos){
    this->_anchor = pos;
}
