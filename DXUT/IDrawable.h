#ifndef UT_I_DRAWABLE_H
#define UT_I_DRAWABLE_H

class IDrawable {
public:
	virtual ~IDrawable() = default;
	virtual void Draw()const = 0;
};
#endif