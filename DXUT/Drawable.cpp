#include "Drawable.h" 


bool Drawable::isDirt()const {
	return _isDirt;
}
void Drawable::SetDirt() {
	_isDirt = true;
}
void Drawable::Clear() {
	_isDirt = false;
}