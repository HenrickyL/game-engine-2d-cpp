#ifndef _MC_ACTION_H
#define _MC_ACTION_H

#include "Action.h"
#include "MCS.h"

class MCAction : public Action<MCS> {

public:
	State<MCS>* Generate(State<MCS>* _target) const override;
	MCS Apply(const State<MCS>* _target) const override;
};

#endif