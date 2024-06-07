#ifndef DXUT_MOVABLE_H
#define DXUT_MOVABLE_H
#include "Position.h"
#include "Vector.h"
#include "DXUT_Math.h"


class Movable {
protected:
    double _rotateRad = 0;
    Vector _rotation = Vector::Zero;
    Position _anchor = Position::Zero;
    Position _positionInitial = Position::Zero;
    Position _position = Position::Zero;
    Vector _speed = Vector::Zero;
    double _magnitude = 0;
public:

    Movable();
    Movable(Position position, Vector speed = Vector::Zero);
    ~Movable();

    Position position() const;
    Position initialPosition() const;
    float x() const;
    float y() const;
    float z() const;
    Vector speed() const;
    double magnitude() const;
    Vector FinalSpeed() const;
    double rotateAngle() const;
    Position anchor() const;
    Vector rotation() const;
    float xRot() const;
    float yRot() const;
    float zRot() const;


    void Speed(const Vector value);
    void Magnitude(const double value);
    void RotateAngle(const double value);
    void Rotation(const Vector& value);
    void RotationX(const float value);
    void RotationY(const float value);
    void RotationZ(const float value);


    void Anchor(Position pos);

    virtual void MoveTo(Position* position);
    virtual void MoveTo(const Position& position);
    virtual void TranslateTo(const Vector& delta);

    /*virtual void RotateTo(const Vector& position);
    virtual void RotateBy(const Vector& delta);*/
};

#endif