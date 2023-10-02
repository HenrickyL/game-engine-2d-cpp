#ifndef DXUT_AI_ACTION_H
#define DXUT_AI_ACTION_H

class State;

class Action {
protected:
	float cost=0.0f;

public:
	Action(float cost = 0.0f);
	float Cost()const;

	virtual State* Generate(State* state)const = 0;
};

inline float Action::Cost() const { return cost; }
#endif