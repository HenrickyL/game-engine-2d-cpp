#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H

#include "State.h"
#include "Action.h"

class Node {
private:
	State* state;
	Action* action;
	Node* father;

public:
	
	Node(State* state, Node* father, Action* action = nullptr);
	float Cost() const;
};

inline float Node::Cost() const { return this->action ? this->action->Cost() : 0.0f; }

#endif
