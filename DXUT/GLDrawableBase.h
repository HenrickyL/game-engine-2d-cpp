#ifndef UT_GLDRAWABLE_BASE_H
#define UT_GLDRAWABLE_BASE_H
#include "IDrawable.h"
#include "Movable.h"


class GLDrawableBase : public virtual IDrawable {
protected:
	int _id;
	bool _initialized = false;
public:
	GLDrawableBase();
	~GLDrawableBase();

	int id() const;
	bool onInitilized()const;

	void Init();
	virtual void InitBuffers();
};

#endif