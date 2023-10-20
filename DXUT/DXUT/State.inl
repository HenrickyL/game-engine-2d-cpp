//#include "State.h"

#include <vector>
#include <string>
#include "Transition.h"
#include "Action.h"


template<typename T>
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
std::string State<T>::Name() const {
    return name;
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
bool State<T>::ExistActionInEdge(Action<T>* action) const {
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
bool State<T>::ExistInKeyInEdge(T _key) const {
    for (const Transition<T>* t : *edges) {
        if (t->GetTarget()->Value() == _key) {
            return true;
        }
    }
    return false;
}

template <typename T>
T State<T>::Value()const {
    return value;
}

template <typename T>
void State<T>::Generate(const std::vector<Action<T>*> actions, State<T>* target, Dictionary<T>* controlGenerated) {
    T min = this->ChooseBestComparison(actions, target);

    for (auto* action : actions) {
        ///TODO: Validar se o estado gerado e valido
        T key = action->Apply(this);
        if (key == min) {
            if (controlGenerated) {
                if (!this->ExistInKeyInEdge(key) && !controlGenerated->Contains(key)) {
                    State<T>* currentGenerated = action->Generate(this);
                    if (currentGenerated && !this->ExistInEdge(currentGenerated)) {
                        AddTransition(new Transition<T>(this, currentGenerated, action));
                        /*if (action->Inverse() != nullptr) {
                            AddTransition(new Transition<T>(currentGenerated, this, action));
                        }*/
                        controlGenerated->Add(key, currentGenerated);
                    }
                }
                else {
                    State<T>* inDictionary = controlGenerated->Get(key);
                    AddTransition(new Transition<T>(this, inDictionary, action));
                    /*if (action->Inverse() != nullptr) {
                        AddTransition(new Transition<T>(inDictionary, this, action));
                    }*/
                }
            }
            else {
                State<T>* currentGenerated = action->Generate(this);
                // Verifique se o novo estado já existe na lista de estados ou se é ambíguo
                if (currentGenerated && !this->ExistInEdge(currentGenerated)) {
                    AddTransition(new Transition<T>(this, currentGenerated, action));
                }
                else {
                    delete currentGenerated; // Descarte o estado ambíguo
                }
            }
            return;
        }
    }
}

