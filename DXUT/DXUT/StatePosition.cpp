#include "StatePosition.h"
//------------------------------------------
#include "Engine.h"
#include "Transition.h"
#include "MovimentAction.h"
//------------------------------------------

Window*& StatePosition::window = Engine::window;


StatePosition::StatePosition(const Position& pos) {
	int x = pos.X();
	int y = pos.Y();
	name = "(x: " + std::to_string(x) + ", y: " + std::to_string(y) + ")";
	_position = new Position(x, y);
}

StatePosition::~StatePosition() {
	delete _position;
}


void StatePosition::Generate(Action* _action) {
	MovimentAction* action = dynamic_cast<MovimentAction*>(_action);
	if (action) {
		StatePosition *target = dynamic_cast<StatePosition*>(action->Generate(this));
		if (!target)
			return;
		edges->push_back(new Transition(target, action));
	}
}

float StatePosition::GetHeuristic(State* _target) const {
	StatePosition* target = dynamic_cast<StatePosition*>(_target);
	if (target) {
		Position p = target->GetPosition();
		return this->GetPosition().Distance(p);
	}
	return 0.0f;
}


void StatePosition::Update() {

}

bool StatePosition::Equal(State* _other) const {
	StatePosition* other = dynamic_cast<StatePosition*>(_other);
	if (other) {
		return this->GetPosition() == other->GetPosition() || this == _other;
	}
	return false;
}


bool StatePosition::IsGeneratedPossible() const {
	return true;
}

