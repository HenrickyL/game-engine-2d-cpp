#ifndef UT_MESH_H
#define UT_MESH_H

#include<vector>
#include "Vertex.h"
#include "types.h" //uint
#include "Movable.h"
#include "Colored.h"
#include "VertexBufferID.h"


class Mesh : public Movable, public Colored {
protected:
    VertexBufferID* _id = nullptr;
    std::vector<Vertex> _vertices;
    std::vector<uint> _indices;
    float _boundingRadius = 0.0f;
    bool _isFlatColor = true;

    void _Clear();

public:
    Mesh();
    Mesh(const Color color);
    Mesh(const Position& position, const Color color = Color::GRAY);
    virtual ~Mesh() = default;

    const std::vector<Vertex>& vertices() const;
    const std::vector<uint>& indices() const;
    float boundingRadius() const;
    bool isFlatColor() const;
    void SetIsFlatColor(bool value);
    VertexBufferID* id()const;
    void SetId(VertexBufferID*);

    virtual void generate();

    bool isDirty()const;
    void Clear();
    void SetDirt();
};

#endif