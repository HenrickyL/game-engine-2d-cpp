#include "GLDrawableBase.h"
#include <GL/glew.h>
#include <stdexcept>

GLDrawableBase::GLDrawableBase(){}

GLDrawableBase::~GLDrawableBase() {
	glDeleteLists(_id, 1);
}

int GLDrawableBase::id() const { return _id; }
bool GLDrawableBase::onInitilized()const { return _initialized; }

void GLDrawableBase::InitBuffers() {
}


void GLDrawableBase::Init() {
}

