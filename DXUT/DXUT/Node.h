#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H

#include "State.h"

class Node {
private:
	State* state;
	float cost = 0;
	Node* father;

public:
	

	float Cost() const;
};

inline float Node::Cost() const { return this->cost; }

#endif
