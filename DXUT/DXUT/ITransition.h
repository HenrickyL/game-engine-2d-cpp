#ifndef DXUT_AI_ITRANSITION_H
#define DXUT_AI_ITRANSITION_H
//------------------------------------------
class IState;
//------------------------------------------

class ITransition {
private:
	IState* target;
public:
	ITransition(IState*& state, float cost);
	virtual void Enter() = 0;	// Método de entrada no estado
	virtual void Execute() = 0; // Método para a lógica do estado
	virtual void Exit() = 0;	// Método de saída do estado
};

#endif