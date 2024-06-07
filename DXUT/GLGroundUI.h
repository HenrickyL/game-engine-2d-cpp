#ifndef UT_GL_Ground_H
#define UT_GL_Ground_H

#include "GroundUI.h"
#include "GLDrawableBase.h"

class GLGroundUI : public GroundUI, public GLDrawableBase {
private:
	void InitBuffers() override;

public:
	GLGroundUI();
	GLGroundUI(int length, const Color color = Color(1,1,1,0.3f));
	GLGroundUI(const Position& pos, int length, const Color color = Color(1, 1, 1, 0.3f));

	void Draw() const override;
	void Init() override;

};

#endif