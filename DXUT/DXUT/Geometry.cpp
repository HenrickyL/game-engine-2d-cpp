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
    // linha padr�o vai de (0,0) at� (0,0)
    a = Point();
    b = Point();
    _type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(const Position& pa, const Position& pb)
{
    // cria linha de (x1,y1) at� (x2,y2)
    a = Point(pa);
    b = Point(pb);
    _type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(const Point& pa, const Point& pb)
{
    // cria linha de pa at� pb
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
    // cria ret�ngulo de (0,0) at� (0,0)
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
    // cria ret�ngulo
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
    // c�rculo padr�o tem raio nulo
    radius = 0;
    _type = CIRCLE_T;
}

// --------------------------------------------------------------------------

Circle::Circle(float r)
{
    // define c�rculo de raio r
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
    vertexCount = 0;                        // pol�gono n�o tem v�rtices
    vertexList = nullptr;                    // inicialmente a lista de v�rtices � vazia
    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(Point* vList, uint vCount)
{
    _position = Position();
    // guarda n�mero de v�rtices do pol�gono
    vertexCount = vCount;

    // aloca mem�ria para os v�rtices
    vertexList = new Point[vCount];

    // guarda lista de v�rtices do pol�gono
    for (uint i = 0; i < vCount; ++i)
        vertexList[i].MoveTo(vList[i].GetPosition());

    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(const Poly& p)
{
    // guarda n�mero de v�rtices do pol�gono
    vertexCount = p.vertexCount;

    // aloca mem�ria para os v�rtices
    vertexList = new Point[vertexCount];

    // guarda lista de v�rtices do pol�gono
    for (uint i = 0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].GetPosition());

    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

const Poly& Poly::operator=(const Poly& p)
{
    if (vertexList)
        delete[] vertexList;

    // guarda n�mero de v�rtices do pol�gono
    vertexCount = p.vertexCount;

    // aloca mem�ria para os v�rtices
    vertexList = new Point[vertexCount];

    // guarda lista de v�rtices do pol�gono
    for (uint i = 0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].GetPosition());

    _type = POLYGON_T;

    return *this;
}

// --------------------------------------------------------------------------

Poly::~Poly()
{
    // libera mem�ria alocada para os v�rtices
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
    // libera a mem�ria ocupa pelas geometrias que comp�em essa forma mista
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
