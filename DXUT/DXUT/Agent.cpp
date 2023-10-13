#include "Agent.h"
//------------------------------------------
#include "Action.h"
#include "Perception.h"
//------------------------------------------

Agent::Agent() {
	actuators = new std::vector<Action<int>*>();
	sensors = new std::vector<Perception*>();
}
//------------------------------------------

Agent::~Agent() {
	DeleteSensors();
	DeleteActuators();
}
//------------------------------------------


void Agent::DeleteSensors() {
	for (int i = 0; i < sensors->size(); i++) {
		Perception* item = sensors->at(i);
		delete item;
	}
	delete sensors;
}
//------------------------------------------

void Agent::DeleteActuators() {
	for (int i = 0; i < actuators->size(); i++) {
		Action<int>* item = actuators->at(i);
		delete item;
	}
	delete actuators;
}
//------------------------------------------


