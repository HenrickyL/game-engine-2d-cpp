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

	//virtual void Enter() = 0;	// Método de entrada no estado
	//virtual void Execute() = 0; // Método para a lógica do estado
	//virtual void Exit() = 0;	// Método de saída do estado
};




#endif