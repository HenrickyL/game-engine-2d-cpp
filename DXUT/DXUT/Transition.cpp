#include "Transition.h"
//------------------------------------------
#include "State.h"
//------------------------------------------

Transition::Transition(State*& state, float _cost) {
	this->target = state;
}