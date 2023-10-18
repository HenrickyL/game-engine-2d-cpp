#include "MovimentAction.h"
#include "Instance.h"
#include "Transition.h"

MovimentAction::MovimentAction(Vector _direction, Action* _inverse) {
	cost = 1.0f;
	direction = _direction;
	inverse = _inverse;
}

State<Position>* MovimentAction::Generate(State<Position>* _state) const {
	Position pos = Apply(_state);
	StatePosition* targetGenerated = new StatePosition(pos);
	return targetGenerated;
}


Position MovimentAction::Apply(const State<Position>* _target) const {
	Position pos = _target->Value();
	pos.Translate(direction * magnitude);
	return pos;
}
