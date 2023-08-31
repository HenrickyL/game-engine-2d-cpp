#ifndef DXUT_AI_TRANSITION_H
#define DXUT_AI_TRANSITION_H
//------------------------------------------
class State;
//------------------------------------------

class Transition {
private:
	State* target;
public:
	Transition(State*& state, float cost);
};

#endif