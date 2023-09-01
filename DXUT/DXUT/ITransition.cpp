#include "ITransition.h"
//------------------------------------------
#include "IState.h"
//------------------------------------------

ITransition::ITransition(IState*& state, float _cost) {
	this->target = state;
}