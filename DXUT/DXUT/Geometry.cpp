#include "Geometry.h"
// --------------------------------------------------------------------------
#include <cmath>

#include "Vector.h"
// --------------------------------------------------------------------------
// Geometry
// --------------------------------------------------------------------------

Geometry::Geometry()
{
    _position = Position();
    _type = UNKNOWN_T;
}

// --------------------------------------------------------------------------

Geometry::~Geometry()
{
}

// --------------------------------------------------------------------------

uint Geometry::Type() const
{
    return _type;
}

Position Geometry::GetPosition() const
{
    return {_position};
}

void Geometry::Translate(const Vector& delta)
{
    _position.Translate(delta);
}

void Geometry::MoveTo(const Position& position)
{
    _position.MoveTo(position);
}


// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

Point::Point()
{
    _position = Position();
    _type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(const Position& position)
{
    MoveTo(position);
    _type = POINT_T;
}

// --------------------------------------------------------------------------
Point::Point(float x, float y)
{
    MoveTo(Position(x, y));
    _type = POINT_T;
}

// --------------------------------------------------------------------------

float Point::Distance(const Point& p) const
{
    return p.GetPosition().Distance(_position);
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
    left = pa.X();
    top = pa.Y();
    right = pb.X();
    bottom = pb.Y();
    _type = RECTANGLE_T;
}

// --------------------------------------------------------------------------
Rect::Rect(const Point& a, const Point& b)
{
    // cria retângulo
    left = a.GetPosition().X();
    top = a.GetPosition().Y();
    right = b.GetPosition().X();
    bottom = b.GetPosition().Y();
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
    _position = Position(r, r);
    radius = r;
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

void Mixed::Translate(const Vector& delta)
{
    _position.Translate(delta);

    for (auto i : shapes)
        i->Translate(delta);
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

// --------------------------------------------------------------------------
