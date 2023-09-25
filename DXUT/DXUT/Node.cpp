#include "Node.h"
//------------------------------------------

#include "State.h"
#include "Action.h"
#include "Transition.h"
//------------------------------------------

Node::Node(State* _state, Action* _action, Node* _father) {
	this->state = _state;
	this->action = _action;
	SetFather(_father);
}

Node::Node(Transition* _transition, Node* _father) {
	this->state = _transition->GetState();
	this->action = _transition->GetAction();
	SetFather(_father);
}

//------------------------------------------

void Node::SetFather(Node* _father) { 
	cost = action ? action->Cost() : 0.0f;
	this->father = _father;
	if (this->father) {
		cost += father->Cost();
	}
}

//------------------------------------------
vector<Node*> Node::Edges(Node* _father) const {
	vector<Node*> result;
	for (Transition* item : *state->Edges()) {
		result.push_back(new Node(item, _father));
	}
	return result;
}


std::string Node::GetPath() {
	std::string res = this->state->Name();
	if (father != nullptr) {
		res += " > " + father->GetPath();
	}
	return res;
}

void Node::DeletePath() {
	if (father)
		father->DeletePath();
	delete father;
}


bool Node::operator<(const Node& other) const {
	return  this->cost > other.cost;
}