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


Position MovimentAction::Apply(State<Position>* _target) const {
	StatePosition* origin = dynamic_cast<StatePosition*>(_target);
	if (origin != nullptr) {
		Position pos = origin->GetPosition();
		pos.Translate(direction * magnitude);
		return pos;
	}
	throw "MovimentAction - State target is not valid";
}
