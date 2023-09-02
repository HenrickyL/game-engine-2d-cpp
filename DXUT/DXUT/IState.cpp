#include "IState.h"
//------------------------------------------
#include "ITransition.h"
//------------------------------------------
IState::IState() {
	edges = new std::vector<ITransition*>();
}
//------------------------------------------
IState::~IState() {
	DeleteEdges();
}
//------------------------------------------
void IState::DeleteEdges() {
	for (int i = 0; i < edges->size(); i++) {
		ITransition* e =edges->at(i);
		delete e;
	}
	delete edges;
}
