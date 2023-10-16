#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include <vector>
#include <string>
//------------------------------------------
// #include "State.h"
// #include "Transition.h"
// #include "Action.h"

template <typename T>
class Transition;

template <typename T>
class Action;
template <typename T>
class Dictionary;


//------------------------------------------

template <typename T>
class State {
protected:
    std::string name;
    T value;
    std::vector<Transition<T>*>* edges;

    void DeleteEdges(){
        for (int i = 0; i < edges->size(); i++) {
        Transition<T>* e = edges->at(i);
        delete e;
        }
        delete edges;
    }

public:
    State(){
        edges = new std::vector<Transition<T>*>();
        name = "default";
    }
    State(std::string _name){
        edges = new std::vector<Transition<T>*>();
        name = _name;
    }

    std::vector<Transition<T>*>* Edges() const{
        return edges;
    }
    std::string Name() const{
        return name;
    }

    void AddTransition(Transition<T>* transition){
        edges->push_back(transition);
    }

    virtual float GetHeuristic(State<T>* target) const{
        return 0.0f;
    }
    virtual bool IsGeneratedPossible() const = 0;
    virtual bool Equal(State<T>* other) const = 0;
    virtual void Generate(const std::vector<Action<T>*> actions, Dictionary<T>* controlGenerated) = 0;
    virtual bool IsAmbiguous(State<T>* newState) const = 0;

    bool ExistActionInEdge(Action<T>* action){
        for (Transition<T>* t : *edges) {
            if (t->GetAction() == action) {
                return true;
            }
        }
        return false;
    }
    bool ExistInEdge(State<T>* _target) const{
        for (const Transition<T>* t : *edges) {
            if (t->GetTarget()->Equal(_target)) {
                return true;
            }
        }
        return false;
    }
    T Value()const {
        return value;
    }
};

#endif
