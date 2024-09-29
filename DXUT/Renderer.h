#ifndef UT_RENDERER_H
#define UT_RENDERER_H

#include "RendererBase.h"
#include "Mesh.h"
#include "Sprite.h"


class Renderer : public RendererBase {
public:
	virtual void Draw(Mesh& shape) = 0;
	virtual void Draw(SpriteData& sprite) = 0;
};
#endif