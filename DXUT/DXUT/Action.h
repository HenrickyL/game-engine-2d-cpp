#ifndef DXUT_AI_ACTION_H
#define DXUT_AI_ACTION_H

template <typename T>
class State;

template <typename T>
class Action {
protected:
    float cost = 0.0f;
    Action<T>* inverse = nullptr;

public:
    Action(float _cost = 0.0f);
    Action(float _cost, Action<T>* _inverse = nullptr);

    float Cost() const;
    Action<T>* Inverse() const;
    void SetInverse(Action<T>* _inverse);

    virtual State<T>* Generate(State<T>* _target) const = 0;
    virtual T Apply(const State<T>* _target) const = 0;

};

#include "Action.inl"
#endif
