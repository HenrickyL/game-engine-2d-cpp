#include "Transition.h"
//------------------------------------------
#include "State.h"
//------------------------------------------

Transition::Transition(State*& state, Action* act) {
	this->target = state;
	this->action = act;
}