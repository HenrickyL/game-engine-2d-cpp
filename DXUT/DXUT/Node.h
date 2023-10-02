#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H
//------------------------------------------
#include <vector>
#include <string>
using std::vector;
#include "Action.h"

//------------------------------------------
class State;
class Transition;
//------------------------------------------


class Node {
private:
	State	*state;
	Action	*action;
	Node	*father;
	State	*target;
	float	cost=0;

public:
	
	Node(State* state, Action* action, Node* father = nullptr);
	Node(Transition* transition, Node* father = nullptr);
	int lenght;
	std::string GetPath();
	int GetPathLength();

	void DeletePath();
	//------------------------------------------
	vector<Node*> Edges(Node* father = nullptr) const;
	float Cost() const;
	State* GetState() const;
	Node* Father() const;
	void GenerateTransitions(vector<Action*> actions);
	bool IsGeneratedPossible() const;
	void SetHeuristicBy(State* target);
	bool Equal(const Node* other) const;
	//------------------------------------------
	void SetFather(Node* father);
	//------------------------------------------
	bool operator<(const Node& other) const;
	//bool operator==(const Node& other) const;


};

inline float Node::Cost() const { return cost; }
inline State* Node::GetState() const { return state; }
inline Node* Node::Father() const { return father; }



//inline bool Node::operator==(const Node& other) const {
//	return this->state == other.state && this->cost == other.cost;
//}


#endif
