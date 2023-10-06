#ifndef STATE_INL
#define STATE_INL


#include "State.h"
#include "Transition.h"
#include "Action.h"

template <typename T>
State<T>::State() {
    edges = new std::vector<Transition<T>*>();
    name = "default";
}

template <typename T>
State<T>::State(std::string _name) {
    edges = new std::vector<Transition<T>*>();
    name = _name;
}

template <typename T>
void State<T>::DeleteEdges() {
    for (int i = 0; i < edges->size(); i++) {
        Transition<T>* e = edges->at(i);
        delete e;
    }
    delete edges;
}

template <typename T>
std::vector<Transition<T>*>* State<T>::Edges() const {
    return edges;
}

template <typename T>
void State<T>::AddTransition(Transition<T>* transition) {
    edges->push_back(transition);
}

template <typename T>
float State<T>::GetHeuristic(State<T>* target) const {
    return 0.0f;
}

template <typename T>
bool State<T>::ExistActionInEdge(Action<T>* action) {
    for (Transition<T>* t : *edges) {
        if (t->GetAction() == action) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool State<T>::ExistInEdge(State<T>* _target) const {
    for (const Transition<T>* t : *edges) {
        if (t->GetTarget()->Equal(_target)) {
            return true;
        }
    }
    return false;
}

template <typename T>
std::string State<T>::Name() const {
    return name;
}

#endif
