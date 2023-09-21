#include "Node.h"


Node::Node(State* _state, Node* _father, Action* _action) {
	this->state = _state;
	this->action = _action;
	this->father = _father;
}