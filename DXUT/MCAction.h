#ifndef _MC_ACTION_H
#define _MC_ACTION_H

#include "Action.h"
#include "MCS.h"

class MCAction : public Action<MCS> {
private:
	int moveMissionary = 0;
	int moveCanibals = 0;

public:
	MCAction(int _missionary, int _canibal);
	State<MCS>* Generate(State<MCS>* _target) const override;
	MCS Apply(const State<MCS>* _target) const override;
	bool IsValid(const MCS _target) const override;
};

#endif