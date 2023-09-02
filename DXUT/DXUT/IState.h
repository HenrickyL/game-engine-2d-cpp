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
	virtual bool IsTriggered() const = 0;		// Método para verificar se a transição deve ocorrer
	virtual IState* GetTargetState() const = 0; // Método para obter o estado de destino da transição
};
#endif