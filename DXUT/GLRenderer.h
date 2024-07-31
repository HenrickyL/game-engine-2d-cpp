#ifndef DX_UT_GL_RENDERER
#define DX_UT_GL_RENDERER

#include "Renderer.h"
#include "GLIncludes.h"
#include "GLImage.h"

class GLRenderer : public Renderer {
private:
	void DrawRect(const Rect& rect) const override;
	void DrawPoint(const Point& point)const override;
	void DrawLine(const Line& line)const override;
	void DrawCircle(const Circle& circle)const override;
	void DrawPolygon(const Poly& polygon)const override;
	void SwitchTypeGeometryToDraw(const Geometry& geometry)const override;

public:
	void Draw(const Geometry& g) override;
	void Draw(SpriteData& sprite) override;
};

#endif