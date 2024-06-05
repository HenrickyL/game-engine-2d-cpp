#ifndef DX_UT_RENDERER_BASE_H
#define DX_UT_RENDERER_BASE_H
// ---------------------------------------------------------------------------
#include "Window.h"
#include "Graphics.h"
// ---------------------------------------------------------------------------
using std::vector;
enum FillModeEnum
{
	F_SOLID=0,
	F_WIREFRAME=1,
	F_POINTS=2,
	F_WIREFRAME_SOLID = 3,
};
// ---------------------------------------------------------------------------
class RendererBase {
protected:
	FillModeEnum    _fillMode = F_SOLID;
public:

	virtual bool Initialize(Window* window, Graphics* graphics);	// inicializa o renderizador
	virtual void Render();                                      // envia sprites para desenho

	void SetFillMode(const FillModeEnum value);
};
// ---------------------------------------------------------------------------
inline void RendererBase::SetFillMode(const FillModeEnum mode) { _fillMode = mode; }
inline bool RendererBase::Initialize(Window* window, Graphics* graphics) { return true; }
inline void RendererBase::Render() {}
#endif