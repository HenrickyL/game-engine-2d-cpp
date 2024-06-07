#include "GLDrawableBase.h"
#include <GL/glew.h>
#include <stdexcept>

GLDrawableBase::GLDrawableBase(){
    _id = glGenLists(1); // Gerar um ID de lista
    if (_id == 0) {
        throw std::runtime_error("Failed to generate OpenGL display list.");
    }
}

GLDrawableBase::~GLDrawableBase() {
	glDeleteLists(_id, 1);
}

int GLDrawableBase::id() const { return _id; }

