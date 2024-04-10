#ifndef DXUT_GEOMETRY_H
#define DXUT_GEOMETRY_H

// ---------------------------------------------------------------------------
#include "Types.h"                                  // tipos da engine
#include <list>                                     // lista da STL
#include "Position.h"
#include "Movable.h"
#include "Color.h"
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

class Geometry : public Movable
{
protected:
    uint _type;                                      // tipo da geometria
    Color _color = Color::GREEN;

public:
    Geometry();// construtor
    Geometry(const Position& position, const Color color);// construtor
    virtual ~Geometry();                            // destrutor

    float X() const { return _position.x(); }
    float Y() const { return _position.y(); }
    virtual Position GetPosition() const;
    virtual uint Type() const;                       // retorna tipo
    virtual Color GetColor() const;

    virtual void SetColor(Color color);

    virtual void MoveTo(const Position& position) override;
    virtual void MoveTo(Position* position) override;
    virtual void TranslateTo(const Vector& delta) override;
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
public:
    Point();                                        // construtor padrão
    Point(float x, float y);                        // construtor usando float
    Point(const Position& position);                // construtor usando pontos-flutuantes

    float Distance(const Point& p) const;          // calcula a distância até outro ponto
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
public:
    Point a, b;                                     // linha vai do ponto A ao ponto B

    Line();                                         // construtor padrão
    Line(float x1, float y1, float x2, float y2);   // construtor usando pontos-flutuantes
    Line(const Position& pa, const Position& pb);   // construtor usando pontos
    Line(const Point& pa, const Point& pb);                     // construtor usando pontos

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

    float Left() const { return _position.x() + left; }       // coordenadas do mundo do menor valor do eixo x
    float Top() const { return _position.y() + top; }        // coordenadas do mundo do menor valor do eixo y
    float Right() const { return _position.x() + right; }      // coordenadas do mundo do maior valor do eixo x
    float Bottom() const { return _position.y() + bottom; }     // coordenadas do mundo do maior valor do eixo y

    float Width() const { return this->_width; }
    float Height() const { return this->_height; }
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
public:
    float radius;                                   // raio do círculo

    Circle();                                       // construtor padrão
    Circle(float r);                                // contrutor com raio

    float CenterX() const { return _position.x() ; }    // coordenadas do mundo do centro (eixo x)
    float CenterY() const { return _position.y(); }    // coordenadas do mundo do centro (eixo y)
};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
public:
    uint    vertexCount;                          // número de vértices 
    Point*  vertexList;                           // vetor de vértices do polígono

    Poly();                                         // construtor padrão
    Poly(Point* vList, uint vCount);               // construtor
    Poly(const Poly& p);                            // construtor de cópia
    ~Poly();                                        // destructor

    const Poly& operator=(const Poly& p);           // operador de atribuição
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
