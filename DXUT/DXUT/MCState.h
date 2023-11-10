#ifndef _MC_STATE_H
#define _MC_STATE_H

#include "State.h"
#include "MCS.h"

class MCState : public State<MCS> {
    bool IsGeneratedPossible() const override;
    bool Equal(State<MCS>* other) const override;
    MCS ChooseBestComparison(const std::vector<Action<MCS>*> actions, State<MCS>* target)const override;
    float GetHeuristic(State<MCS>* target) const;
};

#endif
