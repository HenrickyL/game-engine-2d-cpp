#include "Mesh.h"

Mesh::Mesh() : Movable(Position::Zero), Colored(Color::GRAY) {}
Mesh::Mesh(const Color color): Movable(Position::Zero), Colored(color)  {}
Mesh::Mesh(const Position& position, const Color color): Movable(position), Colored(color){}

const std::vector<Vertex>& Mesh::vertices() const { return _vertices; }
const std::vector<uint>& Mesh::indices() const { return _indices; }
float Mesh::boundingRadius() const { return _boundingRadius; }