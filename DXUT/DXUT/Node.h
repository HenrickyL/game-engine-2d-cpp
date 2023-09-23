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

public:
	
	Node(State* state, Action* action, Node* father = nullptr);
	Node(Transition* transition, Node* father = nullptr);

	std::string GetPath();
	void DeletePath();
	//------------------------------------------
	vector<Node*> Edges(Node* father = nullptr) const;
	float Cost() const;
	State* GetState() const;
	Node* Father() const;
	//------------------------------------------
	void SetFather(Node* father);
	//------------------------------------------
	bool operator==(const Node& other) const;

};

inline float Node::Cost() const { return this->action ? this->action->Cost() : 0.0f; }
inline State* Node::GetState() const { return state; }
inline void Node::SetFather(Node* _father) { father = _father; }
inline Node* Node::Father() const { return father; }

inline bool Node::operator==(const Node& other) const {
	return this->state == other.state && this->action == other.action;
}


#endif
