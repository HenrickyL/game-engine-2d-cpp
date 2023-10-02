#ifndef IA_TEST_MOVIMENT_ACTION_H
#define IA_TEST_MOVIMENT_ACTION_H

#include "Action.h"
#include "Vector.h"
#include "Object.h"
#include "StatePosition.h"

class MovimentAction : public Action {
private:
	float magnitude = 50;
	Vector direction = Vector::Right;
public:
	MovimentAction(Vector _direction);
	State* Generate(State* state)const override;

};


#endif