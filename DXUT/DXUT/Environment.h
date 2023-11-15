// Ambiente || Recebe ações que tem efeitos no ambiente

#ifndef DXUT_AI_ENVIRONMENT_H
#define DXUT_AI_ENVIRONMENT_H
#include<vector>
//------------------------------------------
template<typename T>
class Agent;
//------------------------------------------

template<typename T>
class Environment {
private:
	std::vector<Agent<T>>* agents;
public:
	Environment();
	~Environment();
};
#include "Environment.inl"
#endif