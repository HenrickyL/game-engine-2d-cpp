#ifndef DX_UT_DRAW_GEOMETRY
#define DX_UT_DRAW_GEOMETRY

#include "Geometry.h"

enum FillModeEnum
{
	WIREFRAME = 2,
	SOLID = 3
};

class DrawGeometry {
protected:
	FillModeEnum    _fillMode = SOLID;
private:
	virtual void DrawRect(const Rect& rect) const = 0;
	virtual void DrawPoint(const Point& point) const = 0;
	virtual void DrawLine(const Line& line)const = 0;
	virtual void DrawCircle(const Circle& circle)const = 0;
	virtual void DrawPolygon(const Poly& polygon)const = 0;

public:
	virtual void Draw(const Geometry& g) = 0;
	void SetFillMode(const FillModeEnum value);
};

inline void DrawGeometry::SetFillMode(const FillModeEnum mode)
{_fillMode = mode;}

#endif