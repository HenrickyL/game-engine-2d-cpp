#ifndef UT_RENDERER_3D_H
#define UT_RENDERER_3D_H

#include "RendererBase.h"
#include "Shape3D.h"

class Renderer3D : public RendererBase {
private:
	virtual void DrawCube(const Cube& shape) const = 0;
	virtual void DrawSphere(const Sphere& shape) const = 0;

public:
	virtual void Draw(const Shape3D& shape) = 0;

	virtual void SwitchTypShapeToDraw(const Shape3D& shape) const = 0;
};

#endif