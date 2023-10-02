#include "MovimentAction.h"
#include "Instance.h"

MovimentAction::MovimentAction(Vector _direction) {
	cost = 1.0f;
	direction = _direction;
}

State* MovimentAction::Generate(State* state) const {
	if (instanceOf<StatePosition>(state)) {
		StatePosition* StatePos= (StatePosition*)state;
		Position pos = StatePos->GetPosition();
		pos.Translate(direction * magnitude);
		StatePosition* result = new StatePosition(pos);
		return result;
	}
	return nullptr;
}
