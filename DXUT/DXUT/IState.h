#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include<vector>
//------------------------------------------
class ITransition;
//------------------------------------------

class IState {
private:
	std::vector<ITransition*>* edges;

	void DeleteEdges();
public:
	IState();
	~IState();
	virtual bool IsTriggered() const = 0;		// M�todo para verificar se a transi��o deve ocorrer
	virtual IState* GetTargetState() const = 0; // M�todo para obter o estado de destino da transi��o
};
#endif