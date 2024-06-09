#include "Colored.h"


Colored::Colored(Color color) {
	SetColor(color);
}
Color Colored::color() const { return _color; }
void Colored::SetColor(Color color) { 
	_color = color;
	this->SetDirt();
}