#ifndef UT_SHAPE_3D_H
#define UT_SHAPE_3D_H

#include "Movable.h"
#include "Colored.h"
#include "Vertex.h" 
//#include "Triangle.h" 
#include "types.h"
#include <vector>
using std::vector;
#include <functional>

enum Shape3DType {
    S_UNKNOWN,
    S_SPHERE,
    S_CUBE,
    S_PLANE,
    S_PILL
};


class Shape3D : public Movable, public Colored {
protected:
    Shape3DType _type = S_UNKNOWN;  // Tipo da forma 3D
    Color _color = Color::MAGENTA;
    bool _isFlatColor = true;
    vector<Vertex> _vertices;
    //vector<Triangle> _triangles;
    vector<uint> _indices;
    std::function<void()> _callback;

    void StartGenerate();
    void EndGenerate();
    void NotifyChange();

public:
    Shape3D();
    Shape3D(const Color color);
    Shape3D(const Position& position, const Color color);
    virtual ~Shape3D();

    Shape3DType type() const;
    bool isFlatColor() const;

    void SetIsFlatColor(bool value);
    void SetCallback(std::function<void()> callback);


    const vector<Vertex> vertices() const;
    //const vector<Triangle> triangles() const;
    const vector<uint> indices() const;


    // Métodos adicionais específicos para formas 3D
    virtual void generate() = 0;
    virtual float Volume() const = 0;
    virtual float SurfaceArea() const = 0;
};

// ---------------------------------------------------------------------------
class Cube : public Shape3D {
protected:
    float _width = 1.0f;
    float _height = 1.0f;
    float _depth = 1.0f;

public:
    Cube();
    Cube(const Position& position, const Color color = Color::GREEN);
    Cube(const Position& position, float width, float height, float depth, const Color color = Color::GREEN);
    Cube(const Position& position,float size, const Color color = Color::GREEN);
    Cube(float width, float height, float depth, const Color color = Color::GREEN);
    Cube(float size, const Color color = Color::GREEN);


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
    float _radius = 1.0f;
    int _nStacks = 12;    //latitude
    int _nSectors = 20;   //longitude

public:
    Sphere();
    Sphere(const Position& position, const Color color = Color::GRAY);
    Sphere(float radius, const Color color = Color::GRAY);
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
class Plane : public Shape3D {
private:
    float _width = 1.0f;
    float _height = 1.0f;
    // subdivisions
    int _rows = 4;  
    int _cols = 4;  
public:
    Plane();
    Plane(float edgeSize, const Color& color = Color::WHITE);
    Plane(const Position& position, const Color& color = Color::WHITE);
    Plane(const Position& position, float edgeSize, const Color& color = Color::WHITE);
    Plane(const Position& position, float width, float depth, const Color& color = Color::WHITE);

    float width() const;
    void SetWidth(float value);

    float height() const;
    void SetHeight(float value);

    void generate() override;
    float Volume() const override;
    float SurfaceArea() const override;
};
// ---------------------------------------------------------------------------

class Pill : public Shape3D {
private:
    float _radius = 0.5f;
    float _length = 1.0f;
    int _xSubDiv = 4;
    int _ySubDiv = 4;

public:
    Pill();
    Pill(const Position& position, Color color = Color::YELLOW);
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