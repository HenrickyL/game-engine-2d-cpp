#ifndef _MC_STATE_H
#define _MC_STATE_H

#include "State.h"
#include "MCS.h"

class MCState : public State<MCS> {
public:
    MCState(MCS value);
    bool IsPossibleToGenerate() const override;
    bool Equal(State<MCS>* other) const override;
    PairTypeAction<MCS> ChooseBestComparison(const std::vector<Action<MCS>*> actions, State<MCS>* target)const override;
    float GetHeuristic(State<MCS>* target) const;
    bool IsValid() const override;
};

#endif
