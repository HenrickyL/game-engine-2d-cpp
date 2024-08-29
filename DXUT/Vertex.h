#ifndef UT_VERTEX_H
#define UT_VERTEX_H

#include "Position.h"
#include "Color.h"

struct Vertex {
    // Construtores
    Vertex() : position(), color() {}
    Vertex(const Position& pos, const Color& col) : position(pos), color(col) {}
    Vertex(const Color& col) : position(Position::Zero), color(col) {}


    float x()const { return position.x(); }
    float y()const { return position.y(); }
    float z()const { return position.z(); }

    float r()const { return color.r(); }
    float g()const { return color.g(); }
    float b()const { return color.b(); }

    Position position;
    Color color;
};
#endif