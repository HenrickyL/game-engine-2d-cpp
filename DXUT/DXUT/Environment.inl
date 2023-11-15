//#include "Environment.h"
//------------------------------------------
#include "Agent.h"
//------------------------------------------
template<typename T>
Environment<T>::Environment() {
	agents = new std::vector<Agent>();
}

//------------------------------------------
template<typename T>
Environment<T>::~Environment() {
	delete agents;
}