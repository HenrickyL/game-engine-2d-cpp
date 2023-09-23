#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include<vector>
#include <string>
using std::vector;
//------------------------------------------
class Transition;
//------------------------------------------

class State {
private:
	std::string name;
	vector<Transition*>* edges;
	void DeleteEdges();
public:
	State();
	State(std::string name);
	~State();


	vector<Transition*>* Edges() const;
	std::string Name() const;
	void AddTransition(Transition* transition);

	//------------------------------------------
//	virtual bool IsTriggered() const = 0;		// Método para verificar se a transição deve ocorrer
//	virtual State* GetTargetState() const = 0; // Método para obter o estado de destino da transição
};

inline std::string State::Name() const { return name; }


#endif