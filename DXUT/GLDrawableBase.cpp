#include "GLDrawableBase.h"


GLDrawableBase::GLDrawableBase(int id) :_id(id) {}

int GLDrawableBase::id() const { return _id; }
