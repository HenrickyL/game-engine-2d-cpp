#ifndef DXUT_AI_ACTION_H
#define DXUT_AI_ACTION_H
class Action {
private:
	float cost=0.0f;

public:
	Action(float cost = 0.0f);
	float Cost()const;
};

inline float Action::Cost() const { return cost; }
#endif