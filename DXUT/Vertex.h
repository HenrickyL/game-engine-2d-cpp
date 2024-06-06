#ifndef UT_VERTEX_H
#define UT_VERTEX_H

#include "Position.h"
#include "Color.h"

struct Vertex {
    // Construtores
    Vertex() : position(), color() {}
    Vertex(const Position& pos, const Color& col) : position(pos), color(col) {}

    float x() { return position.x(); }
    float y() { return position.y(); }
    float z() { return position.z(); }

    float r() { return color.r(); }
    float g() { return color.g(); }
    float b() { return color.b(); }

    Position position;
    Color color;
};
#endif