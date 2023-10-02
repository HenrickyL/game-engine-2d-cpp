#include "State.h"
//------------------------------------------
#include "Transition.h"
#include "Action.h"
//------------------------------------------
State::State() {
	edges = new std::vector<Transition*>();
	name = "default";
}

State::State(std::string _name) {
	edges = new std::vector<Transition*>();
	name = _name;
}
//------------------------------------------
State::~State() {
	DeleteEdges();
}
//------------------------------------------
void State::DeleteEdges() {
	for (int i = 0; i < edges->size(); i++) {
		Transition* e =edges->at(i);
		delete e;
	}
	delete edges;
}

vector<Transition*>* State::Edges() const { return edges; }


void State::AddTransition(Transition* transition) {
	edges->push_back(transition);
}



float State::GetHeuristic(State* target) const {
	return 0.0f;
}


//bool State::IsTriggered() const {
//	return true;
//}


//TODO: Verify Performance 
bool State::ExistActionInEdge(Action* action) {
	for (Transition* t : *edges) {
		if (t->GetAction() == action) {
			return true;
		}
	}
	return false;
}

