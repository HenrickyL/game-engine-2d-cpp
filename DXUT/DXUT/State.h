#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include<vector>
using std::vector;
//------------------------------------------
class Transition;
//------------------------------------------

class State {
private:
	vector<Transition*>* edges;

	void DeleteEdges();
public:
	State();
	~State();
	vector<Transition*>* Edges() const;

	//------------------------------------------
	virtual bool IsTriggered() const = 0;		// M�todo para verificar se a transi��o deve ocorrer
	virtual State* GetTargetState() const = 0; // M�todo para obter o estado de destino da transi��o
};


inline vector<Transition*>* State::Edges() const { return edges; }
#endif