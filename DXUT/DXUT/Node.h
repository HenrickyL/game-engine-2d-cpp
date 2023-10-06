#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H
//------------------------------------------
#include <vector>
#include <string>
using std::vector;
#include "Action.h"

//------------------------------------------
template<typename T>
class State;

template<typename T>
class Transition;
//------------------------------------------

template<typename T>
class Node {
private:
	State<T>	*state;
	Action<T>	*action;
	Node	*father;
	State<T>	*target;
	float	cost=0;

public:
	
	Node(State<T>* state, Action<T>* action, Node* father = nullptr);
	Node(Transition<T>* transition, Node* father = nullptr);
	int lenght;
	std::string GetPath();
	int GetPathLength();

	void DeletePath();
	//------------------------------------------
	vector<Node*> Edges(Node* father = nullptr) const;
	float Cost() const;
	State<T>* GetState() const;
	Node* Father() const;
	void GenerateTransitions(const vector<Action<T>*> actions);
	bool IsGeneratedPossible() const;
	void SetHeuristicBy(State<T>* target);
	bool Equal(const Node* other) const;
	//------------------------------------------
	void SetFather(Node* father);
	//------------------------------------------
	bool operator<(const Node& other) const;
	//bool operator==(const Node& other) const;

#include "Node.inl"
};





//inline bool Node::operator==(const Node& other) const {
//	return this->state == other.state && this->cost == other.cost;
//}


#endif
