#include "Color.h"
#ifndef UT_COLORED_H
#define UT_COLORED_H



class Colored {
protected:
	Color _color = Color::GREEN;
public:
	Colored(Color color = Color::MAGENTA);

	Color color() const;
	virtual void SetColor(Color color);
};

#endif