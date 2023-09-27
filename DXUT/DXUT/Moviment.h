#ifndef IA_TEST_MOVIMENT_H
#define IA_TEST_MOVIMENT_H

#include "Action.h"
#include "Vector.h"
#include "Object.h"

class Moviment : public Action {
private:
	Vector direction = Vector::Right;
public:
	Moviment(Vector _direction);
	void Execute(Object* obj);
};


#endif