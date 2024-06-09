#ifndef DXUT_MOVABLE_H
#define DXUT_MOVABLE_H
#include "Position.h"
#include "Vector.h"
#include "Dirtyable.h"
#include <cmath>
#define M_PI 3.14159265358979323846

class Movable : public Dirtyable {
private:
    Vector _rotations = Vector::Zero;
    Position _anchor = Position::Zero;
    Position _positionInitial = Position::Zero;
    Position _position = Position::Zero;
    Vector _speed = Vector::Zero;
    double _magnitude = 0;
public:

    Movable();
    Movable(Position position, Vector speed = Vector::Zero);
    ~Movable();

    const Position position() const;
    const Position initialPosition() const;
    float x() const;
    float y() const;
    float z() const;
    Vector speed() const;
    double magnitude() const;
    Vector FinalSpeed() const;
    const Position anchor() const;
    Vector rotations() const;
    float xRot() const;
    float yRot() const;
    float zRot() const;

    void SetPosition(const Position value);
    void SetSpeed(const Vector value);
    void SetRotation(const Vector value);
    void SetMagnitude(const double value);
    void SetRotationX(const float value);
    void SetRotationY(const float value);
    void SetRotationZ(const float value);
    void SetAnchor(Position pos);

    virtual void MoveTo(Position* position);
    virtual void MoveTo(const Position& position);
    virtual void TranslateTo(const Vector& delta);

    void RotateTo(const Vector& value);
    virtual void RotateBy(const Vector& delta);
};

#endif