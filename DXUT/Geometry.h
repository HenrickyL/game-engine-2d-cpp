#ifndef DXUT_GEOMETRY_H
#define DXUT_GEOMETRY_H

// ---------------------------------------------------------------------------
#include "Types.h"                                  // tipos da engine
#include <list>                                     // lista da STL
#include "Position.h"
#include "Movable.h"
#include "Colored.h"
using std::list;                                    // usar list sem std::
// ---------------------------------------------------------------------------


enum GeometryTypes
{
    UNKNOWN_T,                                      // desconhecido
    POINT_T,                                        // ponto
    LINE_T,                                         // linha
    RECTANGLE_T,                                    // retângulo
    CIRCLE_T,                                       // círculo
    POLYGON_T,                                      // polígono
    MIXED_T                                         // mista
};

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------

class Geometry : public Movable, public Colored
{
protected:
    uint _type;                                      // tipo da geometria
    Color _color = Color::GREEN;
    bool _filled = true;
    float _stroke = 1.0f;
    float _offset = 0.1f;

public:
    Geometry();// construtor
    Geometry(const Position& position, const Color color);// construtor
    virtual ~Geometry();                            // destrutor

    virtual uint type() const;                       // retorna tipo
    virtual bool isFilled() const;
    virtual void setFilled(bool isFilled);

    float Stroke() const;

    void setStroke(float value);


    /*virtual void MoveTo(const Position& position) override;
    virtual void MoveTo(Position* position) override;
    virtual void TranslateTo(const Vector& delta) override;*/
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
private:
    float _size = 1.0f;
public:
    Point();                                                    // construtor padrão
    Point(float x, float y, Color color = Color::RED);                       // construtor usando float
    Point(const Position& position, Color color = Color::RED);  // construtor usando pontos-flutuantes

    float Distance(const Point& p) const;                       // calcula a distância até outro ponto
    float Size() const;

    void setSize(float value);
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
protected:
    Point _a, _b;                                   // linha vai do ponto A ao ponto B
public:


    Line();                                         // construtor padrão
    Line(float x1, float y1, float x2, float y2, Color color = Color::YELLOW);
    Line(const Position& pa, const Position& pb, Color color = Color::YELLOW);   // construtor usando pontos
    Line(const Point& pa, const Point& pb, Color color = Color::YELLOW);                     // construtor usando pontos

    Point A() const;          // Point A
    Point B() const;          // Point B
};

// --------------------------------------------------------------------------
// Rect
// --------------------------------------------------------------------------

class Rect : public Geometry
{
protected:
    float left;                                     // coordenada esquerda do retângulo
    float top;                                      // coordenada superior do retângulo
    float right;                                    // coordenada direita do retângulo
    float bottom;                                   // coordenada inferior do retângulo

    float _width;
    float _height;

public:

    Rect();                                         // construtor padrão
    Rect(const Position& pa, const Position& pb);   // construtor usando pontos-flutuantes
    Rect(const Point& a, const Point& b);                       // construtor usando pontos
    Rect(const Position& center, float width, float height, Color color = Color::GREEN);

    float Left() const { return position().x() + left; }       // coordenadas do mundo do menor valor do eixo x
    float Top() const { return position().y() + top; }        // coordenadas do mundo do menor valor do eixo y
    float Right() const { return position().x() + right; }      // coordenadas do mundo do maior valor do eixo x
    float Bottom() const { return position().y() + bottom; }     // coordenadas do mundo do maior valor do eixo y

    float Width() const { return this->_width; }
    float Height() const { return this->_height; }
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
protected:
    float _radius;                                   // raio do círculo

public:

    Circle();                                       // construtor padrão
    Circle(const Position& p, float r, Color color = Color::MAGENTA); // contrutor com raio

    float Radius() const;
    float OffSet() const;

    void setRadius(float value);

};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
protected:
    list<Point>  _vertexList;
public:
    Poly();                                                              // construtor padrão
    Poly(const Position& pos, Color color = Color::GRAY);                // construtor


    const list<Point> vertexList() const;
    void setVertex(list<Point> vertices);
    void addVertex(const Position& vertex, Color color = Color::GRAY);
    void clear();

    void MoveTo(Position* position) override;
    void MoveTo(const Position& position) override;
    void TranslateTo(const Vector& delta) override;
};

// --------------------------------------------------------------------------
// Mixed
// --------------------------------------------------------------------------

class Mixed : public Geometry
{
public:
    ///TODO: use vector
    list<Geometry*> shapes;                         // lista de formas geométricas

    Mixed();                                        // construtor padrão
    ~Mixed();                                       // destructor

    void Insert(Geometry* s);                      // insere geometria na lista
    void Remove(Geometry* s);                      // remove geometria da lista

    virtual void MoveTo(const Position& position) override;
    virtual void MoveTo(Position* position) override;
    virtual void TranslateTo(const Vector& delta) override;
};

// --------------------------------------------------------------------------

#endif
