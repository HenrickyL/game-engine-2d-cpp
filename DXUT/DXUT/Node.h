#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H
// ------------------------
#include <vector>
#include <string>
#include <stack>
using std::vector;
using std::string;
using std::stack;
#include"Dictionary.h"
// ------------------------
template<typename T>
class State;
template<typename T>
class Action;
template<typename T>
class Transition;

// ------------------------
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
    Node(State<T>* _state, Action<T>* _action, Node<T>* _father = nullptr);
    Node(Transition<T>* _transition, Node<T>* _father = nullptr);

    void DeletePath();
    void GenerateTransitions(const vector<Action<T>*> actions, Dictionary<T>* controlGenerated);
    void SetHeuristicBy(State<T>* _target);
    void SetFather(Node<T>* _father);
    Node<T>* ReversePath();

    std::string GetPath() const;
    int GetPathLength() const;
    vector<Node<T>*> Edges(Node<T>* _father = nullptr) const;
    float Cost() const;
    State<T>* GetState() const;
    Node<T>* Father() const;
    bool IsGeneratedPossible() const;
    bool Equal(const Node<T>* other) const;
    bool operator<(const Node<T>& other) const;
    T Value() const;
};

#include "Node.inl"

#endif

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