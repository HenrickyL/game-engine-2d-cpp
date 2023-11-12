//#include "Agent.h"
//------------------------------------------
#include "Action.h"
#include "Perception.h"
#include "Timer.h"
#include "SearchMethods.h"
#include <iostream>
//------------------------------------------

template<typename T>
void Agent<T>::InstanceAgent() {
	actuators = new std::vector<Action<T>*>();
	sensors = new std::vector<Perception*>();
	InstanceControlGenerated();
}

template<typename T>
void Agent<T>::DeleteInstanceAgent() {
	DeleteSensors();
	DeleteActuators();
}

template<typename T>
void Agent<T>::DeleteSensors() {
	for (int i = 0; i < sensors->size(); i++) {
		Perception* item = sensors->at(i);
		delete item;
	}
	delete sensors;
}
//------------------------------------------
template<typename T>
void Agent<T>::DeleteActuators() {
	for (int i = 0; i < actuators->size(); i++) {
		Action<T>* item = actuators->at(i);
		delete item;
	}
	delete actuators;
}
//------------------------------------------

template<typename T>
void Agent<T>::Search() {
	GenStates();
	if (path != nullptr) {
		deletePath(path);
		path = nullptr;
	}
	float timer = 0;
	Timer t;
	t.Start();
	path = SearchMethods<T>::HeuristicSearch(_initialState, _finalState, *actuators, controlGenerated, Default);
	t.Stop();
	timer = t.Elapsed();
	///TODO: Clear - DEBUG
	std::string res =   path->GetPath();
	pathLength = path != nullptr ? path->GetPathLength() : 0;
}

template<typename T>
void Agent<T>::deletePath(Node<T>* _path) {
	Node<T>* node = _path;
	Node<T>* aux = nullptr;
	while (node != nullptr) {
		aux = node;
		node = node->Father();
		delete aux;
	}
}



template<typename T>
void Agent<T>::SetInitial(T initial) {
	this->_initial = initial;
}

template<typename T>
void Agent<T>::SetFinal(T _final_) {
	this->_final = _final_;

}

template<typename T>
void Agent<T>::SetCurrent(T _current_) {
	this->_current = _current_;

}

template<typename T>
T Agent<T>::Initial() const {
	return this->_initial;
}

template<typename T>
T Agent<T>::Final() const {
	return this->_final;
}

template<typename T>
T Agent<T>::Current() const {
	return _current;
}

template<typename T>
void Agent<T>::InstanceControlGenerated() {
	controlGenerated = new Dictionary<T>();
}


