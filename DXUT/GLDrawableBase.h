#ifndef UT_GLDRAWABLE_BASE_H
#define UT_GLDRAWABLE_BASE_H
#include "IDrawable.h"

class GLDrawableBase : public virtual IDrawable {
protected:
	int _id;
public:
	GLDrawableBase();
	~GLDrawableBase();

	int id() const;
};

#endif