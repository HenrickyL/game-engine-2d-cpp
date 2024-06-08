#include "GLGroundUI.h"
#include <GL/glew.h>
#include <stdexcept>


GLGroundUI::GLGroundUI() {}
GLGroundUI::GLGroundUI(int length, const Color color) : GroundUI(length, color){}
GLGroundUI::GLGroundUI(const Position& pos, int length, const Color color) : GroundUI(pos,length, color) {}

void GLGroundUI::InitBuffers() {

}


void GLGroundUI::Init() {
	if (!_initialized) {
		_id = glGenLists(1); // Gerar um ID de lista
		if (_id == 0) {
			throw std::runtime_error("Failed to generate OpenGL display list.");
		}
		_initialized = true;
	}
}

void GLGroundUI::Draw() const {
	const float* c = this->color().c4f();
	glColor4fv(c);
	glDisable(GL_LINE_SMOOTH);
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
	glEnable(GL_LINE_SMOOTH);
}
