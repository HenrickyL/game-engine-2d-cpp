#ifndef DXUT_AI_SEARCH_BASE_H
#define DXUT_AI_SEARCH_BASE_H
//------------------------------------------
#include "Node.h"
#include "State.h"
#include "SearchStructure.h"
//------------------------------------------

//------------------------------------------

class SearchBase {
private:
	static Node* Search(State* initial, State* final, SearchStructure& method);
public:
	/** Breadth First Search 
	*/
	static Node* BreadthFirstSearch(State* initial, State* final);

	
};
#endif