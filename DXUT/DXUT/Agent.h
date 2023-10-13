// Usa Sensores para Perceber detalhes do ambiente; Tem Ações que podem podem ter Efeitos sobre o Ambiente;
#ifndef DXUT_AI_AGENT_H
#define DXUT_AI_AGENT_H
#include<vector>

class Perception;
template<typename T>
class Action;


class Agent {
private:
	std::vector<Perception*>* sensors;
	std::vector<Action<int>*>* actuators;

	void DeleteSensors();
	void DeleteActuators();

public:
	Agent();
	~Agent();

};

#endif