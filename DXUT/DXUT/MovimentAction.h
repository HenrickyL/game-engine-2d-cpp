#ifndef IA_TEST_MOVIMENT_ACTION_H
#define IA_TEST_MOVIMENT_ACTION_H

#include "Action.h"
#include "Vector.h"
#include "Object.h"
#include "StatePosition.h"

class MovimentAction : public Action<Position> {
private:
	float magnitude = 10;
	Vector direction = Vector::Right;
public:
	MovimentAction(Vector _direction, Action* _inverse = nullptr);
	State<Position>* Generate(State<Position>* state)const override;
	Position Apply(const State<Position>* _target) const override;
	bool IsValid(const Position _target) const override;
};

inline bool MovimentAction::IsValid(const Position _target) const {
	return true;
}
#endif