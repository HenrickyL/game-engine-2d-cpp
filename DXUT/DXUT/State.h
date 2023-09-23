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
	virtual bool IsTriggered() const = 0;		// Método para verificar se a transição deve ocorrer
	virtual State* GetTargetState() const = 0; // Método para obter o estado de destino da transição
};


inline vector<Transition*>* State::Edges() const { return edges; }
#endif