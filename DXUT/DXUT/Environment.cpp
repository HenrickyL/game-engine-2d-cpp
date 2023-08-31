#include "Environment.h"
//------------------------------------------
#include "Agent.h"
//------------------------------------------

Environment::Environment() {
	agents = new std::vector<Agent>();
}

//------------------------------------------
Environment::~Environment() {
	delete agents;
}