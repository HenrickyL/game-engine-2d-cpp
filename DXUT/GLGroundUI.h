#ifndef UT_GL_Ground_H
#define UT_GL_Ground_H

#include "GroundUI.h"
#include "GLDrawableBase.h"

class GLGroundUI : public GroundUI, public GLDrawableBase {
public:
	GLGroundUI();
	GLGroundUI(int length, const Color color = Color::WHITE);
	GLGroundUI(const Position& pos, int length, const Color color = Color::WHITE);

	void Draw() const override;
};

#endif