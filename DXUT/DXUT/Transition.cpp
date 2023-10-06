#include "Transition.h"
//------------------------------------------
#include "State.h"
#include "Action.h"
//------------------------------------------

Transition::Transition(State* _origin, State* _target, Action* _act){
	this->origin = _origin;
	this->target = _target;
	this->action = _act;
}
State*	Transition::GetOrigin() const { return origin; };
State*	Transition::GetTarget() const { return target; };
Action* Transition::GetAction() const { return action; };