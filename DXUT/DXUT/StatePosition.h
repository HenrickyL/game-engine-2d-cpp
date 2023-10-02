#ifndef DXUT_AI_STATE_POSITION_H
#define DXUT_AI_STATE_POSITION_H

#include "State.h"
#include "Object.h"
#include "Window.h"
#include "Action.h"


class StatePosition : public State, public Object {
private:
	static Window*& window;
public:
	StatePosition(const Position& pos);
	~StatePosition();
	void Generate(Action* action) override;
	float GetHeuristic(State* target = nullptr) const override;
	void Update() override;
	bool Equal(State* other) const;
	bool IsGeneratedPossible() const override;
};

#endif