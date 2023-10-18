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
    Action(float _cost = 0.0f) {
        cost = _cost;
    }
    Action(float _cost, Action<T>* _inverse = nullptr) {
        cost = _cost;
        inverse = _inverse;
    }

    float Cost() const {
        return cost;
    }
    Action<T>* Inverse() const {
        return inverse;
    }
    void SetInverse(Action<T>* _inverse) {
        inverse = _inverse;
    }

    virtual State<T>* Generate(State<T>* _target) const = 0;
    virtual T Apply(State<T>* _target) const = 0;

};


#endif
