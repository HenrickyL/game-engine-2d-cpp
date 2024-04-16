#ifndef DX_UT_DRAW_GEOMETRY
#define DX_UT_DRAW_GEOMETRY

#include "Geometry.h"

class DrawGeometry {
private:
	virtual void DrawRect(const Rect& rect) const = 0;
	virtual void DrawPoint(const Point& point) const = 0;

public:
	virtual void Draw(const Geometry& g) = 0;
};

#endif