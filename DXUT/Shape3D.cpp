#include "Shape3D.h"

Shape3D::Shape3D() : Movable(Position::Zero), Colored(Color::GREEN){
    _type = S_UNKNOWN;
}
Shape3D::Shape3D(const Position& position, const Color color) : Movable(position), Colored(color)
{
    _type = S_UNKNOWN;
}

Shape3D::Shape3D(const Color color) : Movable(Position::Zero), Colored(color)
{
    _type = S_UNKNOWN;
}

Shape3D::~Shape3D() {}

bool Shape3D::isFlatColor() const { return _isFlatColor; }
void Shape3D::SetIsFlatColor(bool value) { _isFlatColor = value; }
void Shape3D::SetCallback(std::function<void()> callback) {
    _callback = callback;
}


void Shape3D::NotifyChange(){
    if (_callback) {
        _callback();
    }
}

Shape3DType Shape3D::type() const {
    return _type;
}

const vector<Vertex> Shape3D::vertices() const { return _vertices; }
//const vector<Triangle> Shape3D::triangles() const { return  _triangles; }
const vector<uint> Shape3D::indices() const { return  _indices; }


void Shape3D::StartGenerate() {
    _vertices.clear();
    //_triangles.clear();
    _indices.clear();
}

void Shape3D::EndGenerate() {
    NotifyChange();
}


// ---------------------------------------------------------------------------


Cube::Cube() :Shape3D(Color::BLUE) {
    _type = S_CUBE;
    this->generate();
}
Cube::Cube(const Position& position, const Color color)
    : Shape3D(position, color) {
    _type = S_CUBE;
    this->generate();
}

Cube::Cube(const Position& position, float width, float height, float depth, const Color color)
    : Shape3D(position, color), _width(width), _height(height), _depth(depth){
    _type = S_CUBE;
    this->generate();
}

Cube::Cube(const Position& position, float size, const Color color)
    : Shape3D(position, color), _width(size), _height(size), _depth(size) {
    _type = S_CUBE;
    this->generate();
}

Cube::Cube(float width, float height, float depth, const Color color)
    : Shape3D(color), _width(width), _height(height), _depth(depth) {
    _type = S_CUBE;
    this->generate();
}

Cube::Cube(float size, const Color color)
    : Shape3D(color), _width(size), _height(size), _depth(size) {
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
    this->StartGenerate();

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

    //// Frente
    //_triangles.push_back(Triangle(_vertices[0], _vertices[1], _vertices[2]));
    //_triangles.push_back(Triangle(_vertices[2], _vertices[3], _vertices[0]));
    //// Direita
    //_triangles.push_back(Triangle(_vertices[3], _vertices[2], _vertices[5]));
    //_triangles.push_back(Triangle(_vertices[5], _vertices[4], _vertices[3]));
    //// Traseira
    //_triangles.push_back(Triangle(_vertices[4], _vertices[5], _vertices[6]));
    //_triangles.push_back(Triangle(_vertices[6], _vertices[7], _vertices[4]));
    //// Esquerda
    //_triangles.push_back(Triangle(_vertices[7], _vertices[6], _vertices[1]));
    //_triangles.push_back(Triangle(_vertices[1], _vertices[0], _vertices[7]));
    //// Inferior
    //_triangles.push_back(Triangle(_vertices[1], _vertices[6], _vertices[5]));
    //_triangles.push_back(Triangle(_vertices[5], _vertices[2], _vertices[1]));
    //// Superior
    //_triangles.push_back(Triangle(_vertices[0], _vertices[3], _vertices[4]));
    //_triangles.push_back(Triangle(_vertices[4], _vertices[7], _vertices[0]));

    // Definir os índices dos triângulos
    // Frente
    _indices.push_back(0); _indices.push_back(1); _indices.push_back(2);
    _indices.push_back(2); _indices.push_back(3); _indices.push_back(0);
    // Direita
    _indices.push_back(3); _indices.push_back(2); _indices.push_back(5);
    _indices.push_back(5); _indices.push_back(4); _indices.push_back(3);
    // Traseira
    _indices.push_back(4); _indices.push_back(5); _indices.push_back(6);
    _indices.push_back(6); _indices.push_back(7); _indices.push_back(4);
    // Esquerda
    _indices.push_back(7); _indices.push_back(6); _indices.push_back(1);
    _indices.push_back(1); _indices.push_back(0); _indices.push_back(7);
    // Inferior
    _indices.push_back(1); _indices.push_back(6); _indices.push_back(5);
    _indices.push_back(5); _indices.push_back(2); _indices.push_back(1);
    // Superior
    _indices.push_back(0); _indices.push_back(3); _indices.push_back(4);
    _indices.push_back(4); _indices.push_back(7); _indices.push_back(0);
    EndGenerate();
}


// ---------------------------------------------------------------------------
Sphere::Sphere() :Shape3D(Color::GRAY){
    _type = S_SPHERE;
    this->generate();
}

Sphere::Sphere(const Position& position, const Color color)
    :Shape3D(position, color) {
    _type = S_SPHERE;
    this->generate();
}

Sphere::Sphere(const Position& position, float radius, const Color color)
    :Shape3D(position, color), _radius(radius) {
    _type = S_SPHERE;
    this->generate();
}

Sphere::Sphere(float radius, const Color color)
    :Shape3D(color), _radius(radius) {
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
    this->StartGenerate();

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
        for (int j = 0; j <= nSector; j++) {
            theta = j * deltaTheta;
            float x = temp * sin(theta);
            float z = temp * cos(theta);
            _vertices.push_back(Vertex(Position(x, y, z), isFlatColor()? c : Color::RandomColor()));
        }
    }

    for (int i = 0; i < nStack; i++) {
        for (int j = 0; j < nSector; j++) {
            // calculate indices of the vertices
            /*int v1 = i * nSector + j;
            int v2 = i * nSector + (j + 1) % nSector;
            int v3 = (i + 1) * nSector + (j + 1) % nSector;
            int v4 = (i + 1) * nSector + j;*/
            int current = i * (nSector + 1) + j;
            int next = current + nSector + 1;

            // create triangles
           /* Triangle t1(_vertices[v1], _vertices[v2], _vertices[v3]);
            Triangle t2(_vertices[v1], _vertices[v3], _vertices[v4]);*/
            // Primeiro triângulo
            _indices.push_back(current);
            _indices.push_back(next);
            _indices.push_back(next + 1);

            // Segundo triângulo
            _indices.push_back(current);
            _indices.push_back(next + 1);
            _indices.push_back(current + 1);

            //// add triangles to the list
            //_triangles.push_back(t1);
            //_triangles.push_back(t2);
        }
    }
    EndGenerate();
}
// ---------------------------------------------------------------------------
Plane::Plane() : Shape3D(Color::WHITE){
    _type = S_PLANE;
    this->generate();
}

Plane::Plane(float edgeSize, const Color& color)
    : Shape3D(color), _width(edgeSize), _depth(edgeSize) {
    _type = S_PLANE;
    this->generate();
}
Plane::Plane(const Position& position, float edgeSize, const Color& color)
    : Shape3D(position, color), _width(edgeSize), _depth(edgeSize) {
    _type = S_PLANE;
    this->generate();
}

Plane::Plane(const Position& position, const Color& color)
    : Shape3D(position, color) {
    _type = S_PLANE;
    this->generate();
}

Plane::Plane(const Position& position, float width, float depth, const Color& color)
    : Shape3D(position, color), _width(width), _depth(depth) {
    _type = S_PLANE;
    this->generate();
}

float Plane::width() const {
    return _width;
}

void Plane::SetWidth(float value) {
    _width = value;
    generate();
}

float Plane::depth() const {
    return _depth;
}

void Plane::SetDepth(float value) {
    _depth = value;
    generate();
}

float Plane::Volume() const {
    return 0.0f; // Planes have no volume
}

float Plane::SurfaceArea() const {
    return _width * _depth;
}
void Plane::generate() {
    this->StartGenerate();

    float halfWidth = _width / 2;
    float halfDepth = _depth / 2;
    Color c = this->color();

    int rows = static_cast<int>(_depth / _increment) + 1;
    int cols = static_cast<int>(_width / _increment) + 1;
    // Generate vertices
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float x = j * _increment - halfWidth;
            float y = 0;
            float z = i * _increment - halfDepth;
            _vertices.push_back(Vertex(Position(x, y, z), isFlatColor() ? c : Color::RandomColor()));
        }
    }
    //generate triangles 
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            int topLeft = i * cols + j;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + cols;
            int bottomRight = bottomLeft + 1;

            /*_triangles.push_back(Triangle(_vertices[topLeft], _vertices[bottomLeft], _vertices[topRight]));
            _triangles.push_back(Triangle(_vertices[topRight], _vertices[bottomLeft], _vertices[bottomRight]));*/
            // Primeiro triângulo
            _indices.push_back(topLeft);
            _indices.push_back(bottomLeft);
            _indices.push_back(topRight);

            // Segundo triângulo
            _indices.push_back(topRight);
            _indices.push_back(bottomLeft);
            _indices.push_back(bottomRight);
        }
    }
    EndGenerate();
}

// ---------------------------------------------------------------------------


Pill::Pill() : Shape3D(Color::YELLOW){
    _type = S_PILL;
    this->generate();
}

Pill::Pill(const Position& position,  Color color)
    : Shape3D(position, color) {
    _type = S_PILL;
    this->generate();
}

Pill::Pill(const Position& position, float radius, float length, Color color)
    : Shape3D(position, color), _radius(radius), _length(length) {
    _type = S_PILL;
    this->generate();
}

float Pill::radius() const {
    return _radius;
}

void Pill::SetRadius(float value) {
    _radius = value;
}

float Pill::length() const {
    return _length;
}

void Pill::SetLength(float value) {
    _length = value;
}

float Pill::Volume() const {
    // Volume de um cilindro: V = PI * r^2 * h
    const float PI = 3.14159265359;
    return PI * _radius * _radius * _length;
}

float Pill::SurfaceArea() const {
    // Área da superfície de um cilindro: A = 2PI r(h + r)
    const float PI = 3.14159265359;
    return 2 * PI * _radius * (_length + _radius);
}


void Pill::generate() {
    this->StartGenerate();
    this->EndGenerate();
}