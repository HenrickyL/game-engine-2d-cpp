#include "Mesh.h"

Mesh::Mesh() : Movable(Position::Zero), Colored(Color::GRAY) {}
Mesh::Mesh(const Color color): Movable(Position::Zero), Colored(color)  {}
Mesh::Mesh(const Position& position, const Color color): Movable(position), Colored(color){}

const std::vector<Vertex>& Mesh::vertices() const { return _vertices; }
const std::vector<uint>& Mesh::indices() const { return _indices; }
float Mesh::boundingRadius() const { return _boundingRadius; }
bool Mesh::isFlatColor() const { return _isFlatColor; }
void Mesh::SetIsFlatColor(bool value) { _isFlatColor = value; this->generate(); }

void Mesh::_Clear() {
    // Limpa os vértices e índices existentes
    _vertices.clear();
    _indices.clear();
}


void Mesh::generate() {
    this->_Clear();
}



bool Mesh::isDirty()const {
    return Colored::isDirty() || Movable::isDirty();
}
void Mesh::Clear() {
    Colored::Clear();
    Movable::Clear();
}

void Mesh::SetDirt() {
    Colored::SetDirt();
    Movable::SetDirt();
}


VertexBufferID* Mesh::id()const { return _id; }
void Mesh::SetId(VertexBufferID* value) {
    if (_id)delete _id;
    _id = value;
}