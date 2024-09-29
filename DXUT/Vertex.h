#ifndef UT_VERTEX_H
#define UT_VERTEX_H

#include "Position.h"
#include "Color.h"

struct Vertex {
    // Construtores
    Vertex() : position(Vector::Zero), color() {}
    Vertex(const Vector& pos, const Color& col) : position(pos), color(col) {}
    Vertex(const Color& col) : position(Vector::Zero), color(col) {}


    float x()const { return position.x(); }
    float y()const { return position.y(); }
    float z()const { return position.z(); }

    float r()const { return color.r(); }
    float g()const { return color.g(); }
    float b()const { return color.b(); }

    Vector position;
    Color color;
};
#endif