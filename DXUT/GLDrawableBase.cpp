#include "GLDrawableBase.h"
#include <GL/glew.h>
#include <stdexcept>

GLDrawableBase::GLDrawableBase(){}

GLDrawableBase::~GLDrawableBase() {
	glDeleteLists(_id, 1);
}

int GLDrawableBase::id() const { return _id; }
bool GLDrawableBase::onInitilized()const { return _initialized; }


void GLDrawableBase::init() {
    if (!_initialized) {
        _id = glGenLists(1); // Gerar um ID de lista
        if (_id == 0) {
            throw std::runtime_error("Failed to generate OpenGL display list.");
        }
        _initialized = true;
    }
}

