#ifndef UT_SHAPE_3D_H
#define UT_SHAPE_3D_H

#include "Movable.h"
#include "Colored.h"

enum Shape3DType {
    UNKNOWN,
    SPHERE,
    CUBE,
    CONE,
    // Outros tipos de formas 3D que você deseja suportar
};


class Shape3D : public Movable, public Colored {
protected:
    Shape3DType _type;  // Tipo da forma 3D
    Color _color = Color::GREEN;

public:
    Shape3D();
    Shape3D(const Position& position, const Color color);
    virtual ~Shape3D();

    Shape3DType type() const;

    //virtual void MoveTo(const Position& position);
    //virtual void TranslateTo(const Vector& delta);

    // Métodos adicionais específicos para formas 3D
    virtual float Volume() const = 0;
    virtual float SurfaceArea() const = 0;
};

#endif