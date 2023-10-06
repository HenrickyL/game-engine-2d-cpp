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

//------------------------------------------

template <typename T>
class State {
protected:
    std::string name;
    std::vector<Transition<T>*>* edges;

    void DeleteEdges();

public:
    State();
    State(std::string name);

    std::vector<Transition<T>*>* Edges() const;
    std::string Name() const;
    void AddTransition(Transition<T>* transition);

    virtual float GetHeuristic(State<T>* target) const;
    virtual bool IsGeneratedPossible() const = 0;
    virtual bool Equal(State<T>* other) const = 0;

    virtual void Generate(const std::vector<Action<T>*> actions) = 0;
    virtual bool IsAmbiguous(State<T>* newState) const = 0;

    bool ExistActionInEdge(Action<T>* action);
    bool ExistInEdge(State<T>* _target) const;
};

#include "State.inl"

#endif
