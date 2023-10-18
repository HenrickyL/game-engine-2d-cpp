#ifndef IA_TEST_MOVIMENT_ACTION_H
#define IA_TEST_MOVIMENT_ACTION_H

#include "Action.h"
#include "Vector.h"
#include "Object.h"
#include "StatePosition.h"

class MovimentAction : public Action<Position> {
private:
	float magnitude = 100;
	Vector direction = Vector::Right;
public:
	MovimentAction(Vector _direction, Action* _inverse = nullptr);
	State<Position>* Generate(State<Position>* state)const override;
	Position Apply(State<Position>* _target) const override;
};

#endif