#ifndef DX_UT_GL_DRAW_GEOMETRY
#define DX_UT_GL_DRAW_GEOMETRY

#include "DrawGeometry.h"
#include "GLIncludes.h"

class GLDrawGeometry : public DrawGeometry {
private:
	void DrawRect(const Rect& rect) const override;
	void DrawPoint(const Point& point)const override;
	void DrawLine(const Line& line)const override;
	void DrawCircle(const Circle& circle)const override;
	void DrawPolygon(const Poly& polygon)const override;

public:
	void Draw(const Geometry& g) override;

	bool Initialize(Window* window, Graphics* graphics) override;
	void Draw(SpriteData& sprite) override;
	void Render() override;
};

#endif