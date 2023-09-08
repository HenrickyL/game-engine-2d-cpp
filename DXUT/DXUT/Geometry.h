#ifndef DXUT_GEOMETRY_H
#define DXUT_GEOMETRY_H

// ---------------------------------------------------------------------------
#include "Types.h"                                  // tipos da engine
#include <list>                                     // lista da STL
#include "Position.h"
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

class Geometry
{
protected:
    Position _position;                  // posição da geometria
    uint _type;                                      // tipo da geometria

public:
    Geometry();                                     // construtor
    virtual ~Geometry();                            // destrutor

    float X() const { return _position.X(); }
    float Y() const { return _position.Y(); }
    virtual Position GetPosition() const;
    virtual uint Type() const;                       // retorna tipo 
    virtual void Translate(const Vector& delta);      // move a geometria pelo delta (dx,dy)
    virtual void MoveTo(const Position& position);         // move a geometria para a posição (px,py)
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
public:
    float left;                                     // coordenada esquerda do retângulo
    float top;                                      // coordenada superior do retângulo
    float right;                                    // coordenada direita do retângulo
    float bottom;                                   // coordenada inferior do retângulo

    Rect();                                         // construtor padrão
    Rect(const Position& pa, const Position& pb);   // construtor usando pontos-flutuantes
    Rect(const Point& a, const Point& b);                       // construtor usando pontos

    float Left() const { return _position.X() + left; }       // coordenadas do mundo do menor valor do eixo x
    float Top() const { return _position.Y() + top; }        // coordenadas do mundo do menor valor do eixo y
    float Right() const { return _position.X() + right; }      // coordenadas do mundo do maior valor do eixo x
    float Bottom() const { return _position.Y() + bottom; }     // coordenadas do mundo do maior valor do eixo y
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

    float CenterX() const { return _position.X() + radius; }    // coordenadas do mundo do centro (eixo x)
    float CenterY() const { return _position.Y() + radius; }    // coordenadas do mundo do centro (eixo y)
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

    void Translate(const Vector& delta);             // move a geometria pelo delta (dx,dy)
    void MoveTo(const Position& position);                // move a geometria para a posição (px,py)
};

// --------------------------------------------------------------------------

#endif
