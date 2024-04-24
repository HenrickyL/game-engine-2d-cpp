#include "MCAction.h"
#include "MCState.h"


MCAction::MCAction(int _missionary, int _canibal) {
	moveMissionary = _missionary;
	moveCanibals = _canibal;
	cost = moveMissionary + moveCanibals;
}

State<MCS>* MCAction::Generate(State<MCS>* _target) const {
	MCS next = Apply(_target);
	MCState* targetGenerated = new MCState(next);
	return targetGenerated;
}

MCS MCAction::Apply(const State<MCS>* _target) const {
	MCS current = _target->Value();
	current.Move(moveMissionary,  moveCanibals);
	return current;
}

bool MCAction::IsValid(const MCS _target) const {
	MCState targetGenerated(_target);
	return targetGenerated.IsValid();

}
