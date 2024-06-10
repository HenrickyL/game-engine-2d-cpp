#include "Color.h"
#ifndef UT_COLORED_H
#define UT_COLORED_H

#include "Dirtyable.h"

class Colored : public Dirtyable {
private:
	Color _color = Color::GREEN;
public:
	Colored(Color color = Color::MAGENTA);

	Color color() const;
	void SetColor(Color color);
};

#endif