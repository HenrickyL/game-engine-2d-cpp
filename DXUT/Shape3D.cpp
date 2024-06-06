#include "Shape3D.h"
#include <cmath>

Shape3D::Shape3D() : Movable(Position::Zero) {
    _color = Color::GREEN;
    _type = S_UNKNOWN;
}
Shape3D::Shape3D(const Position& position, const Color color) : Movable(position)
{
    _color = color;
    _type = S_UNKNOWN;
}

Shape3D::~Shape3D() {}

bool Shape3D::isFlatColor() const { return _isFlatColor; }
void Shape3D::SetIsFlatColor(bool value) { _isFlatColor = value; }


Shape3DType Shape3D::type() const {
    return _type;
}

const vector<Vertex> Shape3D::vertices() const { return _vertices; }
const vector<Triangle> Shape3D::triangles() const { return  _triangles; }

// ---------------------------------------------------------------------------


Cube::Cube() :Shape3D(), _width(1.0f), _height(1.0f), _depth(1.0f) {
    _type = S_CUBE;
    SetColor(Color::GREEN);
    this->generate();
}

Cube::Cube(const Position& position, float width, float height, float depth, const Color color)
    : Shape3D(position, color), _width(width), _height(height), _depth(depth){
    _type = S_CUBE;
    this->generate();
}

float Cube::width() const {return _width;}
float Cube::height() const {return _height;}
float Cube::depth() const {return _depth;}

void Cube::SetWidth(float value) { _width = value; }
void Cube::SetHeight(float value){ _height = value; }
void Cube::SetDepth(float value){ _depth = value; }


float Cube::Volume() const {
    return _width * _height * _depth;
}

float Cube::SurfaceArea() const {
    return 2 * (_width * _height + _height * _depth + _depth * _width);
}

void Cube::generate() {
    _vertices.clear();
    _triangles.clear();
    float halfWidth = width() / 2;
    float halfHeight = height() / 2;
    float halfDepth = depth() / 2;

    // Definir os vértices do cubo
    this->_vertices.clear();
    
    Color c = this->color();
    this->_vertices.push_back(Vertex(
        Position(-halfWidth, halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));   // v1
    this->_vertices.push_back(Vertex(
        Position(-halfWidth, -halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));  // v2
    this->_vertices.push_back(Vertex(
        Position(halfWidth, -halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));   // v3
    this->_vertices.push_back(Vertex(
        Position(halfWidth, halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));    // v4
    this->_vertices.push_back(Vertex(
        Position(halfWidth, halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));   // v5
    this->_vertices.push_back(Vertex(
        Position(halfWidth, -halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));  // v6
    this->_vertices.push_back(Vertex(
        Position(-halfWidth, -halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor())); // v7
    this->_vertices.push_back(Vertex(
        Position(-halfWidth, halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));  // v8

    // Frente
    _triangles.push_back(Triangle(_vertices[0], _vertices[1], _vertices[2]));
    _triangles.push_back(Triangle(_vertices[2], _vertices[3], _vertices[0]));
    // Direita
    _triangles.push_back(Triangle(_vertices[3], _vertices[2], _vertices[5]));
    _triangles.push_back(Triangle(_vertices[5], _vertices[4], _vertices[3]));
    // Traseira
    _triangles.push_back(Triangle(_vertices[4], _vertices[5], _vertices[6]));
    _triangles.push_back(Triangle(_vertices[6], _vertices[7], _vertices[4]));
    // Esquerda
    _triangles.push_back(Triangle(_vertices[7], _vertices[6], _vertices[1]));
    _triangles.push_back(Triangle(_vertices[1], _vertices[0], _vertices[7]));
    // Inferior
    _triangles.push_back(Triangle(_vertices[1], _vertices[6], _vertices[5]));
    _triangles.push_back(Triangle(_vertices[5], _vertices[2], _vertices[1]));
    // Superior
    _triangles.push_back(Triangle(_vertices[0], _vertices[3], _vertices[4]));
    _triangles.push_back(Triangle(_vertices[4], _vertices[7], _vertices[0]));
}


// ---------------------------------------------------------------------------
Sphere::Sphere() :Shape3D(), _radius(1.0f){
    _type = S_SPHERE;
    SetColor(Color::GRAY);
    this->generate();
}

Sphere::Sphere(const Position& position, float radius, const Color color)
    :Shape3D(position, color), _radius(radius) {
    _type = S_SPHERE;
    this->generate();
}

float Sphere::radius() const {return _radius;}
void Sphere::SetRadius(float value) {_radius = value;}

float Sphere::sectors() const { return _nSectors; }
void Sphere::SetSectors(float value) { _nSectors = value; }

float Sphere::stacks() const { return _nStacks; }
void Sphere::SetStacks(float value) { _nStacks = value; }


float Sphere::Volume() const {
    return (4.0f / 3.0f) * M_PI * std::pow(_radius, 3);
}

float Sphere::SurfaceArea() const {
    return 4.0f * M_PI * std::pow(_radius, 2);
}

void Sphere::generate() {
    _vertices.clear();
    _triangles.clear();
    //generate Vertex
    float phi; // -pi/2 - pi/2
    float theta; //0 - 2pi
    const float PI = 3.14159265359;

    int nStack = this->stacks();
    int nSector = this->sectors();
    int radius = this->radius();
    Color c = this->color();
    
    float deltaPhi = PI / nStack;
    float deltaTheta = 2 * PI / nSector;

    //generate vertices
    for (int i = 0; i <= nStack; i++) {
        phi = -PI / 2.0 + i * deltaPhi;
        float temp = radius * cos(phi);
        float y = radius * sin(phi);
        for (int j = 0; j < nSector; j++) {
            theta = j * deltaTheta;
            float x = temp * sin(theta);
            float z = temp * cos(theta);
            _vertices.push_back(Vertex(Position(x, y, z), isFlatColor()? c : Color::RandomColor()));
        }
    }

    for (int i = 0; i < nStack; i++) {
        for (int j = 0; j < nSector; j++) {
            // calculate indices of the vertices
            int v1 = i * nSector + j;
            int v2 = i * nSector + (j + 1) % nSector;
            int v3 = (i + 1) * nSector + (j + 1) % nSector;
            int v4 = (i + 1) * nSector + j;

            // create triangles
            Triangle t1(_vertices[v1], _vertices[v2], _vertices[v3]);
            Triangle t2(_vertices[v1], _vertices[v3], _vertices[v4]);

            // add triangles to the list
            _triangles.push_back(t1);
            _triangles.push_back(t2);
        }
    }
}
