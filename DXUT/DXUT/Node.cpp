#include "Node.h"
//------------------------------------------
#include <iostream>
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
	this->state = _transition->GetTarget();
	this->action = _transition->GetAction();
	SetFather(_father);
}


//------------------------------------------

void Node::SetFather(Node* _father) { 
	cost = action ? action->Cost() : 0.0f;
	cost += state->GetHeuristic(target);
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
		res += " > \n\t" + father->GetPath();
	}
	return res;
}

int Node::GetPathLength() {
	if (father == nullptr) return 0;
	return 1 + father->GetPathLength();
}


void Node::DeletePath() {
	if (father)
		father->DeletePath();
	delete father;
}


bool Node::operator<(const Node& other) const {
	return  this->cost > other.cost;
}

void Node::GenerateTransitions(const vector<Action*> actions){
	state->Generate(actions);
}


bool Node::IsGeneratedPossible() const {
	return this->state->IsGeneratedPossible();
}

void Node::SetHeuristicBy(State* _target) {
	target = _target;
}

bool Node::Equal(const Node* other) const {
	return this->GetState()->Equal(other->GetState()) || this == other;
}


