#include "Geometry.h"
// --------------------------------------------------------------------------
#include <cmath>

#include "Vector.h"
// --------------------------------------------------------------------------
// Geometry
// --------------------------------------------------------------------------
Geometry::Geometry() : Movable(Position::Zero){
    _color = Color::GREEN;
    _type = UNKNOWN_T;
}
Geometry::Geometry(const Position& position, const Color color) : Movable(position)
{
    _color = color;
    _type = UNKNOWN_T;
}

// --------------------------------------------------------------------------

Geometry::~Geometry()
{
}

// --------------------------------------------------------------------------
Color Geometry::GetColor() const {
    return this->_color;
}

void Geometry::SetColor(Color color) {
    this->_color = color;
}


uint Geometry::Type() const
{
    return _type;
}

Position Geometry::GetPosition() const
{
    return {_position};
}

void Geometry::TranslateTo(const Vector& delta)
{
    _position.TranslateTo(delta);
}

void Geometry::MoveTo(const Position& position)
{
    _position.MoveTo(position);
}
void Geometry::MoveTo(Position* position)
{
    _position.MoveTo(position);
}


// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

Point::Point(): Geometry(Position::Zero, Color::RED)
{
    _type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(const Position& position, Color color): Geometry(position, color)
{
    _type = POINT_T;
}

// --------------------------------------------------------------------------
Point::Point(float x, float y, Color color): Geometry(Position(x,y), color)
{
    _type = POINT_T;
}

// --------------------------------------------------------------------------

float Point::Distance(const Point& p) const
{
    return p.GetPosition().Distance(_position);
}

float Point::Size()const {
    return this->_size;
}

void Point::setSize(float value) {
    this->_size = value;
}

// --------------------------------------------------------------------------
// Line
// --------------------------------------------------------------------------

Line::Line()
{
    // linha padrão vai de (0,0) até (0,0)
    a = Point();
    b = Point();
    _type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(const Position& pa, const Position& pb)
{
    // cria linha de (x1,y1) até (x2,y2)
    a = Point(pa);
    b = Point(pb);
    _type = LINE_T;
}
// --------------------------------------------------------------------------

Line::Line(float x1, float y1, float x2, float y2)
{
    // cria linha de (x1,y1) até (x2,y2)
    a = Point(x1, y1);
    b = Point(x2, y2);
    _type = LINE_T;
}
// --------------------------------------------------------------------------

Line::Line(const Point& pa, const Point& pb)
{
    // cria linha de pa até pb
    a = pa;
    b = pb;
    _type = LINE_T;
}

Point Line::A() const {
    return a;
}
Point Line::B() const {
    return b;
}

// --------------------------------------------------------------------------
// Rect  
// --------------------------------------------------------------------------

Rect::Rect()
{
    _position = Position();
    // cria retângulo de (0,0) até (0,0)
    left = right = 0.0f;
    top = bottom = 0.0f;
    _type = RECTANGLE_T;
}

// --------------------------------------------------------------------------

Rect::Rect(const Position& pa, const Position& pb)
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
}

// --------------------------------------------------------------------------
Rect::Rect(const Point& a, const Point& b)
{
    float xA = a.GetPosition().x();
    float xB = b.GetPosition().x();
    float yA = a.GetPosition().y();
    float yB = b.GetPosition().y();

    // cria retângulo
    left = xA;
    top = yA;
    right = xB;
    bottom = yB;
    _width = std::abs(xB - xA);
    _height = std::abs(yB - yA);
    _type = RECTANGLE_T;
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
}


// --------------------------------------------------------------------------
// Circle  
// --------------------------------------------------------------------------

Circle::Circle()
{
    _position = Position();
    // círculo padrão tem raio nulo
    radius = 0;
    _type = CIRCLE_T;
}

// --------------------------------------------------------------------------

Circle::Circle(float r)
{
    // define círculo de raio r
    radius = r;
    _position = Position(r, r);
    _type = CIRCLE_T;
}

// --------------------------------------------------------------------------
// Poly 
// --------------------------------------------------------------------------

Poly::Poly()
{
    _position = Position();
    vertexCount = 0;                        // polígono não tem vértices
    vertexList = nullptr;                    // inicialmente a lista de vértices é vazia
    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(Point* vList, uint vCount)
{
    _position = Position();
    // guarda número de vértices do polígono
    vertexCount = vCount;

    // aloca memória para os vértices
    vertexList = new Point[vCount];

    // guarda lista de vértices do polígono
    for (uint i = 0; i < vCount; ++i)
        vertexList[i].MoveTo(vList[i].GetPosition());

    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(const Poly& p)
{
    // guarda número de vértices do polígono
    vertexCount = p.vertexCount;

    // aloca memória para os vértices
    vertexList = new Point[vertexCount];

    // guarda lista de vértices do polígono
    for (uint i = 0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].GetPosition());

    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

const Poly& Poly::operator=(const Poly& p)
{
    if (vertexList)
        delete[] vertexList;

    // guarda número de vértices do polígono
    vertexCount = p.vertexCount;

    // aloca memória para os vértices
    vertexList = new Point[vertexCount];

    // guarda lista de vértices do polígono
    for (uint i = 0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].GetPosition());

    _type = POLYGON_T;

    return *this;
}

// --------------------------------------------------------------------------

Poly::~Poly()
{
    // libera memória alocada para os vértices
    if (vertexList)
        delete[] vertexList;
}


// --------------------------------------------------------------------------
// Mixed 
// --------------------------------------------------------------------------

Mixed::Mixed()
{
    _type = MIXED_T;
    _position = Position();

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
    _position.TranslateTo(delta);
    for (auto i : shapes)
        i->TranslateTo(delta);
}

// --------------------------------------------------------------------------

void Mixed::MoveTo(const Position& position)
{
    for (auto i : shapes)
    {
        i->MoveTo(position);
    }
    _position.MoveTo(position);
}

void Mixed::MoveTo(Position* position)
{
    for (auto i : shapes)
    {
        i->MoveTo(position);
    }
    _position.MoveTo(position);
}

// --------------------------------------------------------------------------
