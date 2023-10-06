#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_METHODS_H
//------------------------------------------
#include "Node.h"
#include "State.h"
#include "SearchStructure.h"
#include "Action.h"
#include <vector>
using std::vector;
//------------------------------------------

//------------------------------------------
template<typename T>
class SearchMethods {
private:
	static const int _MAX = 2000;

	static Node<T>* Search(State<T>* initial, State<T>* final, SearchStructure<T>& method, vector<Action<T>*> actions);

	//------------------------------------------
	static void DeleteNodes(vector<Node<T>*>& nodesToRemove);
	static void DeleteNotInPath(vector<Node<T>*>& nodesToRemove, Node<T>* path);
	static bool existInVector(vector<Node<T>*> list, const Node<T>* element);

	//------------------------------------------
	static Node<T>* SearchAndHandleResult(Node<T>* node, State<T>* target, vector<Node<T>*> AllNodes);
public:
	/** 
		* @brief Breadth First Search 
	*/
	static Node<T>* BreadthFirstSearch(State<T>* initial, State<T>* final);
	/**
		* @brief Deph First Search
	*/
	static Node<T>* DepthFirstSearch(State<T>* initial, State<T>* final);
	// f(n) = g(n) + h(n) - > Custo + Heuristica
	static Node<T>* HeuristicSearch(State<T>* initial, State<T>* final, vector<Action<T>*> actions);
};

#include "SearchMethods.inl"
#endif