#ifndef DXUT_AI_NODE_H
#define DXUT_AI_NODE_H

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "State.h"
#include "Action.h"
#include "Transition.h"

template<typename T>
class Node {
private:
	State<T>* state;
	Action<T>* action;
	Node<T>* father;
	State<T>* target;
	float cost = 0;
	int length;

public:
	Node(State<T>* _state, Action<T>* _action, Node<T>* _father = nullptr);
	Node(Transition<T>* _transition, Node<T>* _father = nullptr);

	std::string GetPath();
	int GetPathLength();
	void DeletePath();

	vector<Node<T>*> Edges(Node<T>* father = nullptr) const;
	float Cost() const;
	State<T>* GetState() const;
	Node<T>* Father() const;
	void GenerateTransitions(const vector<Action<T>*> actions);
	bool IsGeneratedPossible() const;
	void SetHeuristicBy(State<T>* target);
	bool Equal(const Node<T>* other) const;

	void SetFather(Node<T>* father);

	bool operator<(const Node<T>& other) const;
};

#include "Node.inl"

#endif
