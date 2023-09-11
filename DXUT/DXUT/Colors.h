#ifndef DXUT_COLORS_H
#define DXUT_COLORS_H
#include <wingdi.h>
#include "Vector.h"

const COLORREF C_BLACK = RGB(0, 0, 0);
const COLORREF C_WHITE = RGB(255, 255, 255);

struct Color {
	float R = 1.0f;
	float G = 1.0f;
	float B = 1.0f;
	float A = 1.0f;

	Color() : R(1.0f), G(1.0f), B(1.0f), A(1.0f) {}
	Color(float r, float g, float b, float a = 1.0f) : R(fmaxf(0.0f, fminf(1.0f, r))), G(fmaxf(0.0f, fminf(1.0f, g))), B(fmaxf(0.0f, fminf(1.0f, b))), A(a) {}
	Color(const Vector& color, float a = 1.0f) : R(fmaxf(0.0f, fminf(1.0f, color.X()))), G(fmaxf(0.0f, fminf(1.0f, color.Y()))), B(fmaxf(0.0f, fminf(1.0f, color.Z()))), A(fmaxf(0.0f, fminf(1.0f, a))) {}
};

#endif
