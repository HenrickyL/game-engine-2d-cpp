#ifndef UT_VERTEX_H
#define UT_VERTEX_H

#include "Position.h"
#include "Color.h"

struct Vertex {
    // Construtores
    Vertex() : position(), color() {}
    Vertex(const Position& pos, const Color& col) : position(pos), color(col) {}

    Position position;
    Color color;
};
#endif