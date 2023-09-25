#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_BASE_H
//------------------------------------------
#include "Node.h"
#include "State.h"
#include "SearchStructure.h"
//------------------------------------------

//------------------------------------------

class SearchMethods {
private:
	static Node* Search(State* initial, State* final, SearchStructure& method);
	static Node* SearchAndHandleResult(Node* node, State* target, vector<Node*> AllNodes);

public:
	/** 
		* @brief Breadth First Search 
	*/
	static Node* BreadthFirstSearch(State* initial, State* final);
	/**
		* @brief Deph First Search
	*/
	static Node* DepthFirstSearch(State* initial, State* final);

	static Node* HeuristicSearch(State* initial, State* final);

	
};
#endif