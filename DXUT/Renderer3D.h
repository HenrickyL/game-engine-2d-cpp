#ifndef UT_RENDERER_3D_H
#define UT_RENDERER_3D_H

#include "RendererBase.h"
#include "Mesh.h"
#include "Sprite.h"


class Renderer3D : public RendererBase {
private:
	virtual void DrawShape(const Mesh& shape) const =0;

public:
	virtual void Draw(Mesh& shape) = 0;
	virtual void Draw(SpriteData& sprite) = 0;

};

#endif