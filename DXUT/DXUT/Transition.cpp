#include "Transition.h"
//------------------------------------------
#include "State.h"
#include "Action.h"
//------------------------------------------

Transition::Transition(State*& state, Action* act) {
	this->target = state;
	this->action = act;
}

State* Transition::GetState() const { return target; };
Action* Transition::GetAction() const { return action; };