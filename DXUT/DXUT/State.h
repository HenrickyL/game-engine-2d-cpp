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

template<typename T>
struct PairTypeAction {
    T _value;
    Action<T>* _action;
    int _cost;

    PairTypeAction(T value, Action<T>* action, int cost = 0) {
        _value = value;
        _action = action;
        _cost = cost;
    }
};

enum GenerateType {
    HillClimb,
    Default
};

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

    virtual bool IsPossibleToGenerate() const = 0;
    virtual bool Equal(State<T>* other) const = 0;
    virtual PairTypeAction<T> ChooseBestComparison(const std::vector<Action<T>*> actions, State<T>* target)const = 0;
    virtual void Generate(T key, Action<T>* action, Dictionary<T>* controlGenerated);
    virtual void GenerateByBestChoice(const std::vector<Action<T>*> actions, State<T>* target, Dictionary<T>* controlGenerated);
    virtual void GenerateForActions(const std::vector<Action<T>*> actions, State<T>* target, Dictionary<T>* controlGenerated);
    virtual float GetHeuristic(State<T>* target) const;
    virtual bool IsValid() const;


    void AddTransition(Transition<T>* transition);

    std::string Name() const;
    std::vector<Transition<T>*>* Edges() const;
    bool ExistActionInEdge(Action<T>* action) const;
    bool ExistInEdge(State<T>* _target) const;
    bool ExistInKeyInEdge(T _key) const;
    ///TODO: validate whether the name 'Value' is the best, as it will be used as 'Key' later.
    T Value()const;
};
#include "State.inl"
#endif
