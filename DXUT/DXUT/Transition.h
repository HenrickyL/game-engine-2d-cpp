#ifndef DXUT_AI_TRANSITION_H
#define DXUT_AI_TRANSITION_H
//------------------------------------------
//template<typename T>
//class State;
//template<typename T>
//class Action;

#include "State.h"
#include "Action.h"
//------------------------------------------
template<typename T>
class Transition {
private:
	State<T>* origin;
	State<T>* target;
	Action<T>* action;
public:
	Transition(State<T>* _origin, State<T>* _target, Action<T>* _act);

	State<T>*	GetOrigin() const;
	State<T>*	GetTarget() const;
	Action<T>* GetAction() const;

	//virtual void Enter() = 0;	// Método de entrada no estado
	//virtual void Execute() = 0; // Método para a lógica do estado
	//virtual void Exit() = 0;	// Método de saída do estado

#include "Transition.inl"
};




#endif