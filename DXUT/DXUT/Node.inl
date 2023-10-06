#ifndef DXUT_AI_NODE_INL
#define DXUT_AI_NODE_INL

#include "State.h"
#include "Action.h"
#include "Transition.h"


template<typename T>
Node<T>::Node(State<T>* _state, Action<T>* _action, Node<T>* _father) {
    this->state = _state;
    this->action = _action;
    SetFather(_father);
}

template<typename T>
Node<T>::Node(Transition<T>* _transition, Node<T>* _father) {
    this->state = _transition->GetTarget();
    this->action = _transition->GetAction();
    SetFather(_father);
}

template<typename T>
void Node<T>::SetFather(Node<T>* _father) {
    cost = action ? action->Cost() : 0.0f;
    cost += state->GetHeuristic(target);
    this->father = _father;
    if (this->father) {
        cost += father->Cost();
    }
}

template<typename T>
vector<Node<T>*> Node<T>::Edges(Node<T>* _father) const {
    vector<Node<T>*> result;
    for (Transition<T>* item : *state->Edges()) {
        result.push_back(new Node<T>(item, _father));
    }
    return result;
}

template<typename T>
string Node<T>::GetPath() {
    string res = this->state->Name();
    if (father != nullptr) {
        res += " > \n\t" + father->GetPath();
    }
    return res;
}

template<typename T>
int Node<T>::GetPathLength() {
    if (father == nullptr) return 0;
    return 1 + father->GetPathLength();
}

template<typename T>
void Node<T>::DeletePath() {
    if (father)
        father->DeletePath();
    delete father;
}

template<typename T>
bool Node<T>::operator<(const Node<T>& other) const {
    return this->cost > other.cost;
}

template<typename T>
void Node<T>::GenerateTransitions(const vector<Action<T>*> actions) {
    state->Generate(actions);
}

template<typename T>
bool Node<T>::IsGeneratedPossible() const {
    return this->state->IsGeneratedPossible();
}

template<typename T>
void Node<T>::SetHeuristicBy(State<T>* _target) {
    target = _target;
}

template<typename T>
bool Node<T>::Equal(const Node<T>* other) const {
    return this->GetState()->Equal(other->GetState()) || this == other;
}

template<typename T>
float Node<T>::Cost() const { return cost; }

template<typename T>
State<T>* Node<T>::GetState() const { return state; }

template<typename T>
Node<T>* Node<T>::Father() const { return father; }

#endif
