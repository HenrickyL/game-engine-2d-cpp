#include "Moviment.h"


Moviment::Moviment(Vector _direction) {
	cost = 1.0f;
	direction = _direction;
}

void Moviment::Execute(Object* obj) {
	obj->Translate(direction * obj->Magnitude());
}