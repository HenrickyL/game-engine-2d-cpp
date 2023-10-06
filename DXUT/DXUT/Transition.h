#ifndef DXUT_AI_TRANSITION_H
#define DXUT_AI_TRANSITION_H
//------------------------------------------
class State;
class Action;

//------------------------------------------

class Transition {
private:
	State* origin;
	State* target;
	Action* action;
public:
	Transition(State* _origin, State* _target, Action* _act);

	State*	GetOrigin() const;
	State*	GetTarget() const;
	Action* GetAction() const;

	//virtual void Enter() = 0;	// M�todo de entrada no estado
	//virtual void Execute() = 0; // M�todo para a l�gica do estado
	//virtual void Exit() = 0;	// M�todo de sa�da do estado
};




#endif