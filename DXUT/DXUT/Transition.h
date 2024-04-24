#ifndef DXUT_AI_TRANSITION_H
#define DXUT_AI_TRANSITION_H

template <typename T>
class State;

template <typename T>
class Action;

template <typename T>
class Transition {
private:
    State<T>* origin;
    State<T>* target;
    Action<T>* action;

public:
    Transition(State<T>* _origin, State<T>* _target, Action<T>* _act);
    State<T>* GetOrigin() const;
    State<T>* GetTarget() const;
    Action<T>* GetAction() const;
};

#include "Transition.inl"
#endif
