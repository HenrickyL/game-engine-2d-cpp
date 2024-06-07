#ifndef UT_GLDRAWABLE_BASE_H
#define UT_GLDRAWABLE_BASE_H

class GLDrawableBase {
protected:
	int _id;
public:

	GLDrawableBase(int id);
	int id() const;
};

#endif