#include "MCState.h"

MCState::MCState(MCS _value) {
	this->value = _value;
	this->name = _value.ToString();
}


bool MCState::IsGeneratedPossible() const {
	return this->Value().IsValid();
}

bool MCState::Equal(State<MCS>* other) const {
	return this->Value().Equal(other->Value());
}

PairTypeAction<MCS> MCState::ChooseBestComparison(const std::vector<Action<MCS>*> actions, State<MCS>* target)const {
	MCS best;
	float min = FLT_MAX;
	Action<MCS>* actionBest = nullptr;

	for (auto* action : actions) {
		MCS key = action->Apply(this);
		float distance = key.Compare(target->Value());
		if (key.IsValid() && (distance < min || min == FLT_MAX)) {
			min = distance;
			best = key;
			actionBest = action;
		}
	}
	return PairTypeAction<MCS>(best, actionBest, min);
}

float MCState::GetHeuristic(State<MCS>* target) const {
	return this->Value().Compare(target->Value());
}

bool MCState::IsValid() const {
	return this->Value().IsValid();
}