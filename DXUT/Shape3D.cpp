#include "Shape3d.h"


Shape3D::Shape3D() : Movable(Position::Zero) {
    _color = Color::GREEN;
    _type = UNKNOWN;
}
Shape3D::Shape3D(const Position& position, const Color color) : Movable(position)
{
    _color = color;
    _type = UNKNOWN;
}

Shape3D::~Shape3D() {}



Shape3DType Shape3D::type() const {
    return _type;
}
