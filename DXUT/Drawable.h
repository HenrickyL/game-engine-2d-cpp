#ifndef UT_I_DRAWABLE_H
#define UT_I_DRAWABLE_H

class Drawable {
protected:
	bool _isDirt = true;
public:

	virtual bool isDirt()const;
	virtual void SetDirt();
	virtual void Clear();

	virtual ~Drawable() = default;
	virtual void Draw()const = 0;
};
#endif