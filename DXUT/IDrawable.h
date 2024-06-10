#ifndef UT_I_DRAWABLE_H
#define UT_I_DRAWABLE_H

#include "Dirtyable.h"
/// TODO: remover "I" n e mais interface
class IDrawable : public Dirtyable {
public:
	virtual ~IDrawable() = default;
	virtual void Draw() = 0;
};
#endif