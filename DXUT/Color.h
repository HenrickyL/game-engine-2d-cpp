#ifndef DXUT_COLORS_H
#define DXUT_COLORS_H
#include "Vector.h"
#include <string>
#include "types.h" 
using std::string;

//const COLORREF C_BLACK = RGB(0, 0, 0);
//const COLORREF C_WHITE = RGB(255, 255, 255);
//
//struct Color {
//	float R = 1.0f;
//	float G = 1.0f;
//	float B = 1.0f;
//	float A = 1.0f;
//
//	Color() : R(1.0f), G(1.0f), B(1.0f), A(1.0f) {}
//	Color(float r, float g, float b, float a = 1.0f) : R(fmaxf(0.0f, fminf(1.0f, r))), G(fmaxf(0.0f, fminf(1.0f, g))), B(fmaxf(0.0f, fminf(1.0f, b))), A(a) {}
//	Color(const Vector& color, float a = 1.0f) : R(fmaxf(0.0f, fminf(1.0f, color.x()))), G(fmaxf(0.0f, fminf(1.0f, color.y()))), B(fmaxf(0.0f, fminf(1.0f, color.z()))), A(fmaxf(0.0f, fminf(1.0f, a))) {}
//};

class Color {
public:
    // Construtores
    Color() : _r(1.0f), _g(1.0f), _b(1.0f), _a(1.0f) {}
    Color(float red, float green, float blue, float alpha = 1.0f) : _r(red), _g(green), _b(blue), _a(alpha) {}

    // Definições estáticas para cores específicas
    static const Color BLACK;
    static const Color RED;
    static const Color BLUE;
    static const Color GREEN;
    static const Color YELLOW;
    static const Color WHITE;
    static const Color GRAY;
    static const Color MAGENTA;
    static const Color _TRANSPARENT;

    // Métodos de acesso
    float r() const { return _r; }
    float g() const { return _g; }
    float b() const { return _b; }
    float alpha() const { return _a; }

    // Métodos de modificação
    void setR(float red) { _r = red; }
    void setG(float green) { _g = green; }
    void setB(float blue) { _b = blue; }
    void setAlpha(float alpha) { _a = alpha; }

    // Métodos de utilidade
    Color modify(float luminosity) const;
    Color interpolate(const Color& otherColor, float t) const;


    static Color UlongToColor(ulong colorValue);
    static ulong ColorToUlong(const Color& color);

private:
    float _r;
    float _g;
    float _b;
    float _a;
};


#endif
