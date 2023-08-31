#include "State.h"
//------------------------------------------
#include "Transition.h"
//------------------------------------------
State::State() {
	edges = new std::vector<Transition*>();
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
