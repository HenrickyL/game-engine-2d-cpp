#include "Geometry.h"
// --------------------------------------------------------------------------
#include <cmath>

#include "Vector.h"
// --------------------------------------------------------------------------
// Geometry
// --------------------------------------------------------------------------
Geometry::Geometry() : Mesh(){
    _color = Color::GREEN;
    _type = UNKNOWN_T;
}
Geometry::Geometry(const Position& position, const Color color) : Mesh(position, color)
{
    _type = UNKNOWN_T;
}

// --------------------------------------------------------------------------

Geometry::~Geometry()
{
}
float Geometry::Stroke()const {
    return this->_stroke;
}

void Geometry::setStroke(float value) {
    this->_stroke = value;
}
// --------------------------------------------------------------------------



uint Geometry::type() const
{
    return _type;
}


//void Geometry::TranslateTo(const Vector& delta)
//{
//    _position.TranslateTo(delta);
//}
//
//void Geometry::MoveTo(const Position& position)
//{
//    _position.MoveTo(position);
//}
//void Geometry::MoveTo(Position* position)
//{
//    _position.MoveTo(position);
//}

void Geometry::setFilled(bool isFilled) {
    _filled = isFilled;
}

bool Geometry::isFilled() const {
    return _filled;
}


// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

Point::Point(): Geometry(Position::Zero, Color::RED)
{
    _type = POINT_T;
    this->generate();
}

// --------------------------------------------------------------------------

Point::Point(const Position& position, Color color): Geometry(position, color)
{
    _type = POINT_T;
    this->generate();
}

// --------------------------------------------------------------------------
Point::Point(float x, float y, Color color): Geometry(Position(x,y), color)
{
    _type = POINT_T;
    this->generate();
}

// --------------------------------------------------------------------------

float Point::Distance(const Point& p) const
{
    return p.position().Distance(position());
}

float Point::Size()const {
    return this->_size;
}

void Point::setSize(float value) {
    this->_size = value;
}

void Point::generate() {
    Mesh::generate();
    _vertices.push_back(Vertex(_color));
}


// --------------------------------------------------------------------------
// Line
// --------------------------------------------------------------------------

Line::Line() : Geometry(Position::Zero, Color::YELLOW)
{
    // linha padrão vai de (0,0) até (0,0)
    _a = Point();
    _b = Point();
    _type = LINE_T;
    this->generate();
}

// --------------------------------------------------------------------------

Line::Line(const Position& pa, const Position& pb, Color color) : Geometry(Position::CenterTo(pa, pb), color)
{
    // cria linha de (x1,y1) até (x2,y2)
    _a = Point(pa);
    _b = Point(pb);
    _type = LINE_T;
    this->generate();
}
// --------------------------------------------------------------------------
Line::Line(float x1, float y1, float x2, float y2, Color color): Geometry(Position::CenterTo(Position(x1,y1), Position(x2, y2)), color)
{
    // cria linha de (x1,y1) até (x2,y2)
    _a = Point(x1, y1);
    _b = Point(x2, y2);
    _type = LINE_T;
    this->generate();
}
// --------------------------------------------------------------------------

Line::Line(const Point& pa, const Point& pb, Color color): Geometry(Position::CenterTo(pa.position(), pb.position()), color)
{
    // cria linha de pa até pb
    _a = pa;
    _b = pb;
    _type = LINE_T;
    this->generate();
}

Point Line::A() const {
    return _a;
}
Point Line::B() const {
    return _b;
}


void Line::generate() {
    Mesh::generate();

    _vertices.push_back(Vertex(_a.position(), _color));
    _vertices.push_back(Vertex(_b.position(), _color));

    _indices.push_back(0);
    _indices.push_back(1);
}



// --------------------------------------------------------------------------
// Rect  
// --------------------------------------------------------------------------

Rect::Rect(): Geometry(Position::Zero, Color::GREEN), _width(1), _height(1)
{
    // cria retângulo de (0,0) até (0,0)
    left = right = 0.0f;
    top = bottom = 0.0f;
    _type = RECTANGLE_T;
    this->generate();
}

// --------------------------------------------------------------------------

Rect::Rect(const Position& pa, const Position& pb) : Geometry(Position::CenterTo(pa, pb), Color::GREEN)
{
    float xA = pa.x();
    float xB = pb.x();
    float yA = pa.y();
    float yB = pb.y();

    left = xA;
    top = yA;
    right = xB;
    bottom = yB;
    _width = std::abs(xB - xA);
    _height = std::abs(yB - yA);

    _type = RECTANGLE_T;
    this->generate();
}

// --------------------------------------------------------------------------
Rect::Rect(const Point& a, const Point& b)
{
    float xA = a.position().x();
    float xB = b.position().x();
    float yA = a.position().y();
    float yB = b.position().y();

    // cria retângulo
    left = xA;
    top = yA;
    right = xB;
    bottom = yB;
    _width = std::abs(xB - xA);
    _height = std::abs(yB - yA);
    _type = RECTANGLE_T;
    this->generate();
}

Rect::Rect(const Position& center, float width, float height, Color color) : Geometry(center, color) {
    _width = width;
    _height = height;
    float halfWidth = _width / 2;
    float halfHeight = _height / 2;
    left = center.x() - halfWidth;
    top = center.y() - halfHeight;
    right = center.x() + halfWidth;
    bottom = center.y() + halfHeight;
    _type = RECTANGLE_T;
    this->generate();
}


void Rect::generate() {
    // Limpa os vértices e índices existentes
    _vertices.clear();
    _indices.clear();

    float halfWidth = Width()/2;
    float halfHeight = Height()/2;


    // Define os vértices do retângulo
    _vertices.push_back(Vertex(Vector(-halfWidth, -halfHeight, 0.0f), _color));    // v1
    _vertices.push_back(Vertex(Vector(halfWidth, -halfHeight, 0.0f), _color));   // v2
    _vertices.push_back(Vertex(Vector(halfWidth, halfHeight, 0.0f), _color));// v3
    _vertices.push_back(Vertex(Vector(-halfWidth, halfHeight, 0.0f), _color)); // v4

    _indices.push_back(0); _indices.push_back(1); _indices.push_back(2);
    _indices.push_back(2); _indices.push_back(3); _indices.push_back(0);
}


// --------------------------------------------------------------------------
// Circle  
// --------------------------------------------------------------------------

Circle::Circle() : Geometry(Position::Zero, Color::MAGENTA)
{
    // círculo padrão tem raio nulo
    _radius = 0;
    _type = CIRCLE_T;
    this->generate();
}

// --------------------------------------------------------------------------

Circle::Circle(const Position& p, float r, Color color) : Geometry(p, color)
{
    _radius = r;
    _type = CIRCLE_T;
    this->generate();
}

float Circle::Radius() const {
    return _radius;
}

void Circle::setRadius(float value) {
    this->_radius = value;
}

float Circle::OffSet() const {
    return _offset;
}



void Circle::generate() {
    Mesh::generate();

    const int numSegments = 36; // Número de segmentos para aproximar o círculo
    const float PI = 3.14159265359;
    float angleStep = 2.0f * PI / numSegments;

    // Limpa os vértices e índices existentes
    _vertices.clear();
    _indices.clear();

    // Adiciona o vértice central do círculo
    _vertices.push_back(Vertex(Vector::Zero, _color));

    // Geração dos vértices ao redor do círculo
    for (int i = 0; i <= numSegments; ++i) {
        float angle = i * angleStep;
        float x = _radius * cos(angle);
        float y = _radius * sin(angle);
        _vertices.push_back(Vertex(Vector(x, y, 0.0f), _color));
    }

    // Geração dos índices para desenhar os triângulos
    for (int i = 1; i <= numSegments; ++i) {
        _indices.push_back(0); // Centro do círculo
        _indices.push_back(i);
        _indices.push_back(i + 1);
    }
}



// --------------------------------------------------------------------------
// Poly 
// --------------------------------------------------------------------------

Poly::Poly() : Geometry(Position::Zero, Color::GRAY)
{
    _type = POLYGON_T;
    this->generate();
}

// --------------------------------------------------------------------------

Poly::Poly(const Position& pos, Color color ) : Geometry(pos, color)
{
    _type = POLYGON_T;
    this->generate();
}

const list<Point> Poly::vertexList() const {
    return _vertexList;
}

void Poly::setVertex(list<Point> vertices) {
    this->clear();
    _vertexList = vertices;
}
void Poly::addVertex(const Position& vertex, Color color) {
    _vertexList.push_back(Point(vertex, color));
}

void Poly::clear() {
    _vertexList.clear();
}

void Poly::MoveTo(Position* pos) {
    this->MoveTo(pos);
    for (Point& point : _vertexList){
        Vector delta = *pos - point.position();
        point.TranslateTo(delta);
    }
}
void Poly::MoveTo(const Position& pos) {
    this->MoveTo(pos);
    for (Point& point : _vertexList) {
        Vector delta = pos - point.position();
        point.TranslateTo(delta);
    }

}
void Poly::TranslateTo(const Vector& delta) {
    this->TranslateTo(delta);
    for (Point& point : _vertexList) {
        point.TranslateTo(delta);
    }
}

void Poly::generate() {}



// --------------------------------------------------------------------------
// Mixed 
// --------------------------------------------------------------------------

Mixed::Mixed()
{
    _type = MIXED_T;
    this->MoveTo(Position());
}

// --------------------------------------------------------------------------

Mixed::~Mixed()
{
    // libera a memória ocupa pelas geometrias que compõem essa forma mista
    for (auto i : shapes)
        delete i;
}

// --------------------------------------------------------------------------

void Mixed::Insert(Geometry* s)
{
    shapes.push_back(s);
}

// --------------------------------------------------------------------------

void Mixed::Remove(Geometry* s)
{
    auto i = find(shapes.begin(), shapes.end(), s);
    shapes.erase(i);
}

// --------------------------------------------------------------------------

void Mixed::TranslateTo(const Vector& delta)
{
    this->TranslateTo(delta);
    for (auto i : shapes)
        i->TranslateTo(delta);
}

// --------------------------------------------------------------------------

void Mixed::MoveTo(const Position& pos)
{
    for (auto i : shapes)
    {
        i->MoveTo(pos);
    }
    this->MoveTo(pos);
}

void Mixed::MoveTo(Position* pos)
{
    for (auto i : shapes)
    {
        i->MoveTo(pos);
    }
    this->MoveTo(pos);
}

void Mixed::generate() {}


// --------------------------------------------------------------------------
