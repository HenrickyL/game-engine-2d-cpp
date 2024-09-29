#include "Shape3D.h"

Shape3D::Shape3D() : Mesh(){
    _type = S_UNKNOWN;
}
Shape3D::Shape3D(const Position& position, const Color color) : Mesh(position, color)
{
    _type = S_UNKNOWN;
}

Shape3D::Shape3D(const Color color) : Mesh(color)
{
    _type = S_UNKNOWN;
}

Shape3D::~Shape3D() {
    delete _id;
}


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



void Shape3D::UpdateBoundingRadius() { 
    float distance ;
    for (const auto& vertex : _vertices) {
        const Position p = vertex.position;
        distance = position().Distance(p);
        if (distance > _boundingRadius) {
            _boundingRadius = distance;
        }
    }
}


void Shape3D::StartGenerate() {
    _vertices.clear();
    //_triangles.clear();
    _indices.clear();
}

void Shape3D::EndGenerate() {
    UpdateBoundingRadius();
    NotifyChange();
}


void Shape3D::_AddFace(int i1, int i2, int i3) {
    _indices.push_back(i1); _indices.push_back(i2); _indices.push_back(i3);

    // Calcular normal da face
    Vector v1 = _vertices[i1].position;
    Vector v2 = _vertices[i2].position;
    Vector v3 = _vertices[i3].position;
    
    Vector normal = Vector::CrossProduct(v2 - v1, v3 - v1); // Normalizada

    if (normal.Module() > 0) {  // Módulo maior que zero significa que a normal é válida
        _normals.push_back(normal.Unitary());
    }
    else {
        // Lidar com a situação em que a normal não é válida (opcional)
        _normals.push_back(Vector::Zero);  // Por exemplo, adicionar uma normal padrão
    }
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
        Vector(-halfWidth, halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));   // v1
    this->_vertices.push_back(Vertex(
        Vector(-halfWidth, -halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));  // v2
    this->_vertices.push_back(Vertex(
        Vector(halfWidth, -halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));   // v3
    this->_vertices.push_back(Vertex(
        Vector(halfWidth, halfHeight, halfDepth), isFlatColor()? c: Color::RandomColor()));    // v4
    this->_vertices.push_back(Vertex(
        Vector(halfWidth, halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));   // v5
    this->_vertices.push_back(Vertex(
        Vector(halfWidth, -halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));  // v6
    this->_vertices.push_back(Vertex(
        Vector(-halfWidth, -halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor())); // v7
    this->_vertices.push_back(Vertex(
        Vector(-halfWidth, halfHeight, -halfDepth), isFlatColor()? c: Color::RandomColor()));  // v8


    // Definir os índices e calcular normais
    // Frente
    _AddFace(0, 1, 2);
    _AddFace(2, 3, 0);
    // Direita
    _AddFace(3, 2, 5);
    _AddFace(5, 4, 3);
    // Traseira
    _AddFace(4, 5, 6);
    _AddFace(6, 7, 4);
    // Esquerda
    _AddFace(7, 6, 1);
    _AddFace(1, 0, 7);
    // Inferior
    _AddFace(1, 6, 5);
    _AddFace(5, 2, 1);
    // Superior
    _AddFace(0, 3, 4);
    _AddFace(4, 7, 0);

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
    int _stacks = this->stacks();
    int _sectors = this->sectors();

    // Geração dos vértices
    const float PI = 3.14159265359;
    float deltaPhi = PI / _stacks;
    float deltaTheta = 2.0f * PI / _sectors;

    for (int i = 0; i <= _stacks; ++i) {
        float phi = -PI / 2.0f + i * deltaPhi;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);

        for (int j = 0; j <= _sectors; ++j) {
            float theta = j * deltaTheta;
            float x = cos(theta) * cosPhi;
            float y = sinPhi;
            float z = sin(theta) * cosPhi;
            _vertices.push_back(Vertex(Vector(x, y, z) * _radius, isFlatColor() ? color() : Color::RandomColor()));
        }
    }

    // Geração dos índices
    for (int i = 0; i < _stacks; ++i) {
        for (int j = 0; j < _sectors; ++j) {
            int topRight = i * (_sectors + 1) + j;
            int bottomRight = topRight + 1;
            int topLeft = topRight + _sectors + 1;
            int bottomLeft = topLeft + 1;
            try
            {
                _AddFace(topRight, bottomRight, bottomLeft);
                _AddFace(topRight, bottomLeft, topLeft);
            }
            catch (const std::exception&)
            {
                int x = 0;
                _AddFace(topRight, bottomRight, bottomLeft);
                _AddFace(topRight, bottomLeft, topLeft);
            }
            
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
    : Shape3D(color), _width(edgeSize), _height(edgeSize) {
    _type = S_PLANE;
    this->generate();
}
Plane::Plane(const Position& position, float edgeSize, const Color& color)
    : Shape3D(position, color), _width(edgeSize), _height(edgeSize) {
    _type = S_PLANE;
    this->generate();
}

Plane::Plane(const Position& position, const Color& color)
    : Shape3D(position, color) {
    _type = S_PLANE;
    this->generate();
}

Plane::Plane(const Position& position, float width, float depth, const Color& color)
    : Shape3D(position, color), _width(width), _height(depth) {
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

float Plane::height() const {
    return _height;
}

void Plane::SetHeight(float value) {
    _height = value;
    generate();
}

float Plane::Volume() const {
    return 0.0f; // Planes have no volume
}

float Plane::SurfaceArea() const {
    return _width * _height;
}
void Plane::generate() {
    this->StartGenerate();

    float halfWidth = _width / 2;
    float halfHeight = _height / 2;
    Color c = this->color();

    float rowIncrement = _height / static_cast<float>(_rows);
    float colIncrement = _width / static_cast<float>(_cols);
    // Generate vertices
    for (int i = 0; i <= _rows; i++) {
        float z = i * rowIncrement - halfHeight;
        for (int j = 0; j <= _cols; j++) {
            float x = j * colIncrement - halfWidth;
            float y = 0;
            _vertices.push_back(Vertex(Vector(x, y, z), isFlatColor() ? c : Color::RandomColor()));
        }
    }
    //generate triangles 
    for (int i = 0; i < _rows ; i++) {
        for (int j = 0; j < _cols; j++) {
            int topLeft = i * (_cols + 1) + j;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + (_cols + 1);
            int bottomRight = bottomLeft + 1;

            _AddFace(topLeft, bottomLeft, topRight);
            _AddFace(topRight, bottomLeft, bottomRight);
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