// Usa Sensores para Perceber detalhes do ambiente; Tem Ações que podem podem ter Efeitos sobre o Ambiente;
#ifndef DXUT_AI_AGENT_H
#define DXUT_AI_AGENT_H

#include<vector>
#include "Dictionary.h"
#include "Node.h"
class Perception;
template<typename T>
class Action;

template<typename T>
class Agent {
protected:
	//search
	T _initial;
	T _final;
	T _current;
	int pathLength = 0;
	Node<T>* path = nullptr;
	Node<T>* pivot = nullptr;
	//state
	State<T>* _initialState = nullptr;
	State<T>* _finalState = nullptr;
	std::vector<Perception*>* sensors;
	std::vector<Action<T>*>* actuators;
	//
	Dictionary<T>* controlGenerated;

	void DeleteSensors();
	void DeleteActuators();
	//search methods
	void deletePath(Node<T>* _path);
	void InstanceAgent();
	void DeleteInstanceAgent();
	virtual void InstanceControlGenerated();
public:
	Agent() = default;
	//------------------------------
	void Search(GenerateType generateType = HillClimb);
	void ClearMemory();
	virtual void GenStates() = 0;
	//------------------------------
	void SetInitial(T initial);
	void SetFinal(T _final_);
	void SetCurrent(T _current_);
	//------------------------------
	T Initial() const;
	T Final() const;
	T Current() const;
};

#include "Agent.inl"
#endif