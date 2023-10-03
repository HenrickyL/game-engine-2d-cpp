#ifndef DXUT_AI_ACTION_H
#define DXUT_AI_ACTION_H

class State;

class Action {
protected:
	float cost=0.0f;
	Action* inverse = nullptr;

public:
	Action(float cost = 0.0f);
	Action(float cost, Action* _inverse = nullptr);

	float Cost()const;
	Action* Inverse() const;
	void SetInverse(Action* _inverse);



	virtual State* Generate(State* _target)const = 0;
};

inline float Action::Cost() const { return cost; }
inline Action* Action::Inverse() const { return inverse; }
inline void Action::SetInverse(Action* _inverse) { inverse = _inverse; };


#endif