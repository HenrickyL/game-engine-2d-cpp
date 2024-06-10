#ifndef UT_GL_ORIGIN_GIZMO_UI_H
#define UT_GL_ORIGIN_GIZMO_UI_H

#include "OriginGizmoUI.h"
#include "GLDrawableBase.h"
#include "types.h"

class GLOriginGizmoUI : public OriginGizmoUI, public GLDrawableBase {
public:
	GLOriginGizmoUI();
	GLOriginGizmoUI(int length);
	GLOriginGizmoUI(const Position& pos, int length = 2.0f);

	void Draw() override;

private:
	uint _vao = 0;
	uint _vbo = 0;
	void InitBuffers() override;
};


#endif