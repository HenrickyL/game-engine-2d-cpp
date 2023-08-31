// Usa Sensores para Perceber detalhes do ambiente; Tem A��es que podem podem ter Efeitos sobre o Ambiente;
#ifndef DXUT_AI_AGENT_H
#define DXUT_AI_AGENT_H
#include<vector>

class Perception;
class Action;


class Agent {
private:
	std::vector<Perception*>* sensors;
	std::vector<Action*>* actuators;

	void DeleteSensors();
	void DeleteActuators();

public:
	Agent();
	~Agent();

};

#endif