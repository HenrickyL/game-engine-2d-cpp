#include "Action.h"


Action::Action(float _cost) {
	cost = _cost;
}

Action::Action(float _cost, Action* _inverse) {
	cost = _cost;
	inverse = _inverse;
}
