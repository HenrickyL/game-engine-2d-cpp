#ifndef DX_UT_RENDERER
#define DX_UT_RENDERER

#include "Geometry.h"
#include "Window.h"
#include "Graphics.h"
#include "Sprite.h"
#include <vector>

using std::vector;
enum FillModeEnum
{
	WIREFRAME = 2,
	SOLID = 3
};

class Renderer {
protected:
	FillModeEnum    _fillMode = SOLID;
	vector<SpriteData*> spriteVector;

private:
	virtual void DrawRect(const Rect& rect) const = 0;
	virtual void DrawPoint(const Point& point) const = 0;
	virtual void DrawLine(const Line& line)const = 0;
	virtual void DrawCircle(const Circle& circle)const = 0;
	virtual void DrawPolygon(const Poly& polygon)const = 0;

public:
	virtual void Draw(const Geometry& g) = 0;

	virtual bool Initialize(Window* window, Graphics* graphics) = 0;  // inicializa o renderizador
	virtual void Draw(SpriteData& sprite) = 0;                  // adiciona _sprite na lista
	virtual void Render() = 0;                                        // envia sprites para desenho

	void SetFillMode(const FillModeEnum value);
};

inline void Renderer::SetFillMode(const FillModeEnum mode)
{_fillMode = mode;}

#endif