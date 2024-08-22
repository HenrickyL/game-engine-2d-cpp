#ifndef UT_MESH_H
#define UT_MESH_H

#include<vector>
#include "Vertex.h"
#include "types.h" //uint
#include "Movable.h"
#include "Colored.h"


class Mesh : public Movable, public Colored {
protected:
    std::vector<Vertex> _vertices;
    std::vector<uint> _indices;
    float _boundingRadius = 0.0f;

public:
    Mesh();
    Mesh(const Color color);
    Mesh(const Position& position, const Color color);
    virtual ~Mesh() = default;

    const std::vector<Vertex>& vertices() const;
    const std::vector<uint>& indices() const;
    float boundingRadius() const;

    virtual void generate() = 0;
};

#endif