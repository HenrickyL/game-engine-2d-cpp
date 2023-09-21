#ifndef DXUT_AI_SEARCH_BASE_H
#define DXUT_AI_SEARCH_BASE_H
//------------------------------------------
#include "Node.h"
#include "State.h"
//------------------------------------------

//------------------------------------------

class SearchBase {
private:
public:
	Node* Search(State* initial, State* final);
	
};
#endif