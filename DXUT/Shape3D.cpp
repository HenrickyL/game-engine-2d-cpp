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

// ---------------------------------------------------------------------------


Cube::Cube() : Shape3D(), _width(1.0f), _height(1.0f), _depth(1.0f) {
    _type = CUBE;
    SetColor(Color::BLUE);
}

Cube::Cube(const Position& position, const Color color, float width, float height, float depth)
    : Shape3D(position, color), _width(width), _height(height), _depth(depth) {
    _type = CUBE;
}

float Cube::width() const {return _width;}
float Cube::height() const {return _height;}
float Cube::depth() const {return _depth;}
bool Cube::isFlatColor() const { return _isFlatColor;}

void Cube::SetWidth(float value) { _width = value; }
void Cube::SetHeight(float value){ _height = value; }
void Cube::SetDepth(float value){ _depth = value; }


float Cube::Volume() const {
    return _width * _height * _depth;
}

float Cube::SurfaceArea() const {
    return 2 * (_width * _height + _height * _depth + _depth * _width);
}
