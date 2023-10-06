#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_METHODS_H
//------------------------------------------
#include "Node.h"
#include "State.h"
#include "SearchStructure.h"
#include <vector>
using std::vector;
//------------------------------------------

//------------------------------------------

class SearchMethods {
private:
	static const int _MAX = 2000;
	static Node* Search(State* initial, State* final, SearchStructure& method, vector<Action*> actions);

	//------------------------------------------
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
	// f(n) = g(n) + h(n) - > Custo + Heuristica
	static Node* HeuristicSearch(State* initial, State* final, vector<Action*> actions);
	
};

#endif