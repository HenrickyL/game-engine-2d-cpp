// Ambiente || Recebe ações que tem efeitos no ambiente

#ifndef DXUT_AI_ENVIRONMENT_H
#define DXUT_AI_ENVIRONMENT_H
#include<vector>
//------------------------------------------
class Agent;
//------------------------------------------
class Environment {
private:
	std::vector<Agent>* agents;
public:
	Environment();
	~Environment();
};
#endif