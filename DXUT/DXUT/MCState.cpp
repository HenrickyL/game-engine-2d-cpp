#include "MCState.h"



MCState::MCState(MCS _value) {
	this->value = _value;
}


bool MCState::IsGeneratedPossible() const {
	return this->Value().Valid();
}

bool MCState::Equal(State<MCS>* other) const {
	return this->Value().Equal(other->Value());
}

MCS MCState::ChooseBestComparison(const std::vector<Action<MCS>*> actions, State<MCS>* target)const {
	MCS best;
	float min = FLT_MAX;
	for (auto* action : actions) {
		MCS key = action->Apply(this);
		float distance = key.Compare(target->Value());
		if (distance < min) {
			min = distance;
			best = key;
		}
	}
	return best;
}

float MCState::GetHeuristic(State<MCS>* target) const {
	return this->Value().Compare(target->Value());
}