#ifndef DX_UT_RENDERER
#define DX_UT_RENDERER
// ---------------------------------------------------------------------------
#include "RendererBase.h"
#include "Sprite.h"
#include <vector>
// ---------------------------------------------------------------------------
using std::vector;

// ---------------------------------------------------------------------------
class Renderer : public RendererBase {
protected:
	vector<SpriteData*> spriteVector;

private:
	virtual void DrawRect(const Rect& rect) const = 0;
	virtual void DrawPoint(const Point& point) const = 0;
	virtual void DrawLine(const Line& line)const = 0;
	virtual void DrawCircle(const Circle& circle)const = 0;
	virtual void DrawPolygon(const Poly& polygon)const = 0;
	virtual void SwitchTypeGeometryToDraw(const Geometry& geometry) const = 0;
public:
	virtual void Draw(const Geometry& g) = 0;

	virtual void Draw(SpriteData& sprite) = 0;
};
// ---------------------------------------------------------------------------
#endif