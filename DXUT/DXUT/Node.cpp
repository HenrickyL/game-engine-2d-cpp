#include "Node.h"
//------------------------------------------

#include "State.h"
#include "Action.h"
#include "Transition.h"
//------------------------------------------

Node::Node(State* _state, Action* _action, Node* _father = nullptr) {
	this->state = _state;
	this->action = _action;
	this->father = _father;
}

Node::Node(Transition* _transition, Node* _father = nullptr) {
	this->state = _transition->GetState();
	this->action = _transition->GetAction();
	this->father = _father;
}

//------------------------------------------
vector<Node*> Node::Edges(Node* _father) const {
	vector<Node*> result;
	for (Transition* item : *state->Edges()) {
		result.push_back(new Node(item, _father));
	}
	return result;
}