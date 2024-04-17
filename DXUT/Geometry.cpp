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
float Geometry::Stroke()const {
    return this->_stroke;
}

void Geometry::setStroke(float value) {
    this->_stroke = value;
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
    return p.position().Distance(_position);
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

Line::Line() : Geometry(Position::Zero, Color::YELLOW)
{
    // linha padrão vai de (0,0) até (0,0)
    _a = Point();
    _b = Point();
    _type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(const Position& pa, const Position& pb, Color color) : Geometry(Position::CenterTo(pa, pb), color)
{
    // cria linha de (x1,y1) até (x2,y2)
    _a = Point(pa);
    _b = Point(pb);
    _type = LINE_T;
}
// --------------------------------------------------------------------------
Line::Line(float x1, float y1, float x2, float y2, Color color): Geometry(Position::CenterTo(Position(x1,y1), Position(x2, y2)), color)
{
    // cria linha de (x1,y1) até (x2,y2)
    _a = Point(x1, y1);
    _b = Point(x2, y2);
    _type = LINE_T;
}
// --------------------------------------------------------------------------

Line::Line(const Point& pa, const Point& pb, Color color): Geometry(Position::CenterTo(pa.position(), pb.position()), color)
{
    // cria linha de pa até pb
    _a = pa;
    _b = pb;
    _type = LINE_T;
}

Point Line::A() const {
    return _a;
}
Point Line::B() const {
    return _b;
}



// --------------------------------------------------------------------------
// Rect  
// --------------------------------------------------------------------------

Rect::Rect(): Geometry(Position::Zero, Color::GREEN)
{
    // cria retângulo de (0,0) até (0,0)
    left = right = 0.0f;
    top = bottom = 0.0f;
    _type = RECTANGLE_T;
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

Circle::Circle() : Geometry(Position::Zero, Color::MAGENTA)
{
    // círculo padrão tem raio nulo
    _radius = 0;
    _type = CIRCLE_T;
}

// --------------------------------------------------------------------------

Circle::Circle(const Position& p, float r, Color color) : Geometry(p, color)
{
    _radius = r;
    _type = CIRCLE_T;
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



// --------------------------------------------------------------------------
// Poly 
// --------------------------------------------------------------------------

Poly::Poly() : Geometry(Position::Zero, Color::GRAY)
{
    _type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(const Position& pos, Color color ) : Geometry(pos, color)
{
    _type = POLYGON_T;
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

void Poly::MoveTo(Position* position) {
    _position.MoveTo(position);
    for (Point& point : _vertexList){
        Vector delta = *position - point.position();
        point.TranslateTo(delta);
    }
}
void Poly::MoveTo(const Position& position) {
    _position.MoveTo(position);
    for (Point& point : _vertexList) {
        Vector delta = position - point.position();
        point.TranslateTo(delta);
    }

}
void Poly::TranslateTo(const Vector& delta) {
    _position.TranslateTo(delta);
    for (Point& point : _vertexList) {
        point.TranslateTo(delta);
    }
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
