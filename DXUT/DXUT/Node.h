#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H

#include <vector>
#include <string>
#include <stack>
using std::vector;
using std::string;
using std::stack;


#include "State.h"
#include "Action.h"
#include "Transition.h"

//#include "State.h"
//#include "Action.h"
//#include "Transition.h"

template<typename T>
class Node {
private:
	State<T>* state;
	Action<T>* action;
	Node<T>* father = nullptr;
	State<T>* target;
	float cost = 0;
	int length;

public:
    Node(State<T>* _state, Action<T>* _action, Node<T>* _father = nullptr) {
        this->state = _state;
        this->action = _action;
        SetFather(_father);
    }
    Node(Transition<T>* _transition, Node<T>* _father = nullptr) {
        this->state = _transition->GetTarget();
        this->action = _transition->GetAction();
        SetFather(_father);
    }

    std::string GetPath() {
        string res = this->state->Name();
        if (father != nullptr) {
            res += " > \n\t" + father->GetPath();
        }
        return res;
    }

    int GetPathLength() {
        if (father == nullptr) return 0;
        return 1 + father->GetPathLength();
    }
    void DeletePath() {
        if (father)
            father->DeletePath();
        delete father;
    }

    vector<Node<T>*> Edges(Node<T>* _father = nullptr) const {
        vector<Node<T>*> result;
        for (Transition<T>* item : *state->Edges()) {
            result.push_back(new Node<T>(item, _father));
        }
        return result;
    }
    float Cost() const { return cost; }
    State<T>* GetState() const { return state; }
    Node<T>* Father() const { return father; }
    void GenerateTransitions(const vector<Action<T>*> actions, Dictionary<T>* controlGenerated) {
        state->Generate(actions, controlGenerated);
    }

    bool IsGeneratedPossible() const {
        return this->state->IsGeneratedPossible();
    }

    void SetHeuristicBy(State<T>* _target) {
        target = _target;
    }
    bool Equal(const Node<T>* other) const {
        return this->GetState()->Equal(other->GetState()) || this == other;
    }

    void SetFather(Node<T>* _father) {
        cost = action ? action->Cost() : 0.0f;
        cost += state->GetHeuristic(target);
        this->father = _father;
        if (this->father) {
            cost += father->Cost();
        }
    }

    bool operator<(const Node<T>& other) const {
        return this->cost > other.cost;
    }

    /*Node<T>* RevertPath() {
        Node<T>* node = this;
        stack<Node<T>*> s;
        while (node != nullptr) {
            s.push(node);
            node = node->Father();
        }
        node = s.top();
        Node<T>* aux1 =nullptr;
        Node<T>* aux2 = nullptr;
        while (!s.empty()) {
            aux1 = s.top();
            s.pop();
            if (!s.empty()) {
                aux2 = s.top();
                s.pop();
                s.push(aux2);
            }
            else {
                aux2 = nullptr;
            }
            aux1->SetFather(aux2);
        }
        return node;
    }*/

    Node<T>* ReversePath() {
        Node<T>* node = this;
        Node<T>* next = nullptr;
        Node<T>* aux = nullptr;

        while (node != nullptr) {
            next = node->Father();
            node->SetFather(aux);
            aux = node;
            node = next;
        }
        return aux;
    }


    T Value() const {
        return state->Value();
    }
};


#endif
