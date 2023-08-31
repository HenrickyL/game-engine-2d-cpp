#ifndef DXUT_AI_STATE_H
#define DXUT_AI_STATE_H
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
};
#endif