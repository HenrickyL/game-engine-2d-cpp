#ifndef DX_UT_GL_DRAW_GEOMETRY
#define DX_UT_GL_DRAW_GEOMETRY

#include "DrawGeometry.h"
#include <GLFW/glfw3.h>
//#include <gl/GLU.h>

class GLDrawGeometry : public DrawGeometry {
private:
	void DrawRect(const Rect& rect) const override;
	void DrawPoint(const Point& point)const override;


public:
	void Draw(const Geometry& g) override;
};

#endif