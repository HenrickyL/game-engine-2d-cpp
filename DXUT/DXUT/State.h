#ifndef DXUT_AI_ISTATE_H
#define DXUT_AI_ISTATE_H
//------------------------------------------
#include <vector>
#include <string>
//------------------------------------------
template <typename T>
class Transition;

template <typename T>
class Action;
#include "Dictionary.h"
//------------------------------------------

//State.h
template <typename T>
class State {
protected:
    std::string name;
    T value;
    std::vector<Transition<T>*>* edges;

    void DeleteEdges();
public:
    State();
    State(std::string _name);

    virtual bool IsGeneratedPossible() const = 0;
    virtual bool Equal(State<T>* other) const = 0;
    virtual void Generate(const std::vector<Action<T>*> actions, Dictionary<T>* controlGenerated);

    void AddTransition(Transition<T>* transition);

    std::string Name() const;
    std::vector<Transition<T>*>* Edges() const;
    virtual float GetHeuristic(State<T>* target) const;
    bool ExistActionInEdge(Action<T>* action) const;
    bool ExistInEdge(State<T>* _target) const;
    bool ExistInKeyInEdge(T _key) const;
    ///TODO: validate whether the name 'Value' is the best, as it will be used as 'Key' later.
    T Value()const;
};
#include "State.inl"
#endif
