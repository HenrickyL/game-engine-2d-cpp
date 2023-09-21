#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include<vector>
//------------------------------------------
class Transition;
//------------------------------------------

class State {
private:
	std::vector<Transition*>* edges;

	void DeleteEdges();
public:
	State();
	~State();
	virtual bool IsTriggered() const = 0;		// Método para verificar se a transição deve ocorrer
	virtual State* GetTargetState() const = 0; // Método para obter o estado de destino da transição
};
#endif