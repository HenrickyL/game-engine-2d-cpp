#ifndef UT_SHAPE_3D_H
#define UT_SHAPE_3D_H

#include "Movable.h"
#include "Colored.h"
#include "Vertex.h" 
#include "Triangle.h" 

#include <vector>
using std::vector;

enum Shape3DType {
    S_UNKNOWN,
    S_SPHERE,
    S_CUBE,
    S_PILL
};


class Shape3D : public Movable, public Colored {
protected:
    Shape3DType _type;  // Tipo da forma 3D
    Color _color = Color::MAGENTA;
    bool _isFlatColor = false;
    vector<Vertex> _vertices;
    vector<Triangle> _triangles;

public:
    Shape3D();
    Shape3D(const Position& position, const Color color);
    virtual ~Shape3D();

    Shape3DType type() const;
    bool isFlatColor() const;
    void SetIsFlatColor(bool value);

    const vector<Vertex> vertices() const;
    const vector<Triangle> triangles() const;

    // Métodos adicionais específicos para formas 3D
    virtual void generate() = 0;
    virtual float Volume() const = 0;
    virtual float SurfaceArea() const = 0;
};

// ---------------------------------------------------------------------------
class Cube : public Shape3D {
protected:
    float _width;
    float _height;
    float _depth;

public:
    Cube();
    Cube(const Position& position, float width, float height, float depth, const Color color = Color::GREEN);

    float width() const;
    float height() const;
    float depth() const;

    void SetWidth(float value);
    void SetHeight(float value);
    void SetDepth(float value);

    void generate() override;
    float Volume() const override;
    float SurfaceArea() const override;
};
// ---------------------------------------------------------------------------
class Sphere : public Shape3D {
private:
    float _radius;
    int _nStacks = 12;    //latitude
    int _nSectors = 20;   //longitude

public:
    Sphere();
    Sphere(const Position& position, float radius, const Color color = Color::GRAY);

    float radius() const;
    void SetRadius(float value);

    float sectors() const;
    void SetSectors(float value);

    float stacks() const;
    void SetStacks(float value);

    void generate() override;
    float Volume() const override;
    float SurfaceArea() const override;
};
// ---------------------------------------------------------------------------

class Pill : public Shape3D {
private:
    float _radius;
    float _length;

public:
    Pill();
    Pill(const Position& position, float radius, float length, Color color = Color::YELLOW);

    float radius() const;
    void SetRadius(float value);

    float length() const;
    void SetLength(float value);

    void generate() override;
    float Volume() const override;
    float SurfaceArea() const override;

};

#endif