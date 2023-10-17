#include "MovimentAction.h"
#include "Instance.h"
#include "Transition.h"

MovimentAction::MovimentAction(Vector _direction, Action* _inverse) {
	cost = 1.0f;
	direction = _direction;
	inverse = _inverse;
}

State<Position>* MovimentAction::Generate(State<Position>* _state) const {
	StatePosition* origin = dynamic_cast<StatePosition*>(_state);
	if(origin != nullptr) {
		Position pos = origin->GetPosition();
		pos.Translate(direction * magnitude);
		StatePosition* targetGenerated = new StatePosition(pos);
		///TODO: check the need for the inverse
		if(inverse)
			targetGenerated->AddTransition(new Transition<Position>(targetGenerated, origin, inverse));
		return targetGenerated;
	}
	return nullptr;
}
