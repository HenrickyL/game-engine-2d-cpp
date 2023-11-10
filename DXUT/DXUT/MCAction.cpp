#include "MCAction.h"
#include "MCState.h"


MCAction::MCAction(int _missionary, int _canibal) {
	moveMissionary = _missionary;
	moveCanibals = _canibal;
}

State<MCS>* MCAction::Generate(State<MCS>* _target) const {
	MCS pos = Apply(_target);
	MCState* targetGenerated = new MCState(pos);
	return targetGenerated;
}

MCS MCAction::Apply(const State<MCS>* _target) const {
	MCS current = _target->Value();
	current.Move(moveMissionary,  moveCanibals);
	return current;
}