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
	virtual void Enter() = 0;	// M�todo de entrada no estado
	virtual void Execute() = 0; // M�todo para a l�gica do estado
	virtual void Exit() = 0;	// M�todo de sa�da do estado
};

#endif