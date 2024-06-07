#include "GLGroundUI.h"
#include <GL/glew.h>


GLGroundUI::GLGroundUI() {}
GLGroundUI::GLGroundUI(int length, const Color color) : GroundUI(length, color){}
GLGroundUI::GLGroundUI(const Position& pos, int length, const Color color) : GroundUI(pos,length, color) {}

void GLGroundUI::Draw() const {
	glColor3fv(this->color().c3f());

	glBegin(GL_LINES);
		for (int i = -_length; i <= _length; i+=_increment) {
			//vertical
			glVertex3f(i, y(), -_length);
			glVertex3f(i, y(), _length);

			//horizontal
			glVertex3f(-_length, y(), i);
			glVertex3f(_length, y(), i);
		}
		glEnd();
}
