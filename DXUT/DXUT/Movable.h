#ifndef DXUT_MOVABLE_H
#define DXUT_MOVABLE_H
#include "Position.h"
#include "Vector.h"
#include <cmath>
#define M_PI 3.14159265358979323846


class Movable {
protected:
    int _rotateRad = 0;
    Position _anchor;
    Position _positionInitial;
    Position _position;
    Vector _speed = Vector::Zero;
    double _magnitude;
public:
    Movable(Position position, Vector speed = Vector::Zero);
    ~Movable();

    Position position() const;
    Position initialPosition() const;
    int x() const;
    int y() const;
    int z() const;
    Vector speed() const;
    double magnitude() const;
    Vector FinalSpeed() const;
    double rotateAngle() const;
    Position anchor() const;

    void Speed(const Vector value);
    void Magnitude(const double value);
    void RotateAngle(const int value);
    void Anchor(Position pos);

    virtual void MoveTo(const Position& position);
    virtual void MoveTo(Position* position);
    virtual void TranslateTo(const Vector& delta);
};

#endif