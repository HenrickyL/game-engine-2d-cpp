#ifndef DXUT_AI_TRANSITION_H
#define DXUT_AI_TRANSITION_H
//------------------------------------------
class State;
class Action;

//------------------------------------------

class Transition {
private:
	State* target;
	Action* action;
public:
	Transition(State*& state, Action* act);


	State* GetState() const;
	Action* GetAction() const;

	//virtual void Enter() = 0;	// Método de entrada no estado
	//virtual void Execute() = 0; // Método para a lógica do estado
	//virtual void Exit() = 0;	// Método de saída do estado
};




#endif