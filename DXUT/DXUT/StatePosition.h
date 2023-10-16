#ifndef DXUT_AI_STATE_POSITION_H
#define DXUT_AI_STATE_POSITION_H

#include "State.h"
#include "Object.h"
#include "Window.h"
#include "Action.h"
#include "Position.h"
#include <vector>
using std::vector;

class StatePosition : public State<Position>, public Object {
private:
	static Window*& window;
public:
	StatePosition(const Position& pos);
	~StatePosition();
	
	//void	Generate(const vector<Action<Position>*> actions, Dictionary<Position>* controlGenerated) override;
	float	GetHeuristic(State<Position>* target = nullptr) const override;
	void	Update() override;
	bool	Equal(State<Position>* other) const;
	bool	IsGeneratedPossible() const override;
	bool	IsAmbiguous(State<Position>* newState) const override;
};

#endif