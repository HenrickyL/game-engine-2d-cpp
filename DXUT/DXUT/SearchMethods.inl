#ifndef SEARCHMETHODS_INL
#define SEARCHMETHODS_INL

#include "Node.h"
#include "State.h"
#include "SearchStructure.h"
#include "Action.h"
#include <vector>
using std::vector;


template <typename T>
Node<T>* SearchMethods<T>::Search(State<T>* initial, State<T>* _final, SearchStructure<T>& edge, vector<Action<T>*> actions) {
    Node<T>* node = new Node<T>(initial, nullptr);
    edge.Push(node);

    vector<Node<T>*> read;
    vector<Node<T>*> AllNodes;
    AllNodes.push_back(node);

    while (!edge.IsEmpty()) {
        node = edge.Pop();

        if (!actions.empty()) {
            node->GenerateTransitions(actions);
        }

        read.push_back(node);

        for (Transition<T>* elem : *node->GetState()->Edges()) {
            Node<T>* chield = new Node<T>(elem, node);
            AllNodes.push_back(chield);

            if (!existInVector(read, chield) && !edge.Exist(chield)) {
                if (chield->GetState() == _final) {
                    return SearchMethods::SearchAndHandleResult(chield, _final, AllNodes);
                }
                edge.Push(chield);
            }
        }
    }
    DeleteNodes(AllNodes);
    return nullptr;
}

template <typename T>
void SearchMethods<T>::DeleteNodes(vector<Node<T>*>& nodesToRemove) {
    for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); it++) {
        if (*it) delete* it;
    }
}

template <typename T>
void SearchMethods<T>::DeleteNotInPath(vector<Node<T>*>& nodesToRemove, Node<T>* path) {
    queue<Node<T>*> q;
    Node<T>* node = path;

    while (node != nullptr) {
        q.push(node);
        node = node->Father();
    }

    while (!q.empty()) {
        node = q.front();
        q.pop();

        for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); it++) {
            Node<T>* item = *it;
            if (item == node) {
                nodesToRemove.erase(it);
                break;
            }
        }
    }
}

template <typename T>
bool SearchMethods<T>::existInVector(vector<Node<T>*> list, const Node<T>* element) {
    for (const auto* item : list) {
        if (item->Equal(element)) return true;
    }
    return false;
}

template <typename T>
Node<T>* SearchMethods<T>::SearchAndHandleResult(Node<T>* node, State<T>* target, vector<Node<T>*> AllNodes) {
    DeleteNotInPath(AllNodes, node);
    DeleteNodes(AllNodes);
    return node;
}

template <typename T>
Node<T>* SearchMethods<T>::HeuristicSearch(State<T>* initial, State<T>* _final, vector<Action<T>*> actions) {
    int count = 0;
    Node<T>* node = new Node<T>(initial, nullptr);
    node->SetHeuristicBy(_final);

    PriorityQueueSearch<T> edge;
    edge.Push(node);

    vector<Node<T>*> read;
    vector<Node<T>*> AllNodes;
    AllNodes.push_back(node);

    while (!edge.IsEmpty()) {
        node = edge.Pop();
        count++;

        if (node->GetState()->Equal(_final)) {
            return SearchMethods<T>::SearchAndHandleResult(node, _final, AllNodes);
        }

        if (node->IsGeneratedPossible() && !actions.empty()) {
            node->GenerateTransitions(actions);
        }

        read.push_back(node);

        for (Transition<T>* elem : *node->GetState()->Edges()) {
            Node<T>* chield = new Node<T>(elem, node);
            chield->SetHeuristicBy(_final);
            AllNodes.push_back(chield);

            if (!existInVector(read, chield) && !edge.Exist(chield)) {
                edge.Push(chield);
            }
            else {
                if (edge.ExistLargeThan(chield)) {
                    edge.RemoveLargeThanBy(chield);
                    edge.Push(chield);
                }
                else if (count > ::SearchMethods<T>::_MAX) {
                    return SearchMethods<T>::SearchAndHandleResult(chield, _final, AllNodes);
                }
            }
        }
    }
    DeleteNodes(AllNodes);
    return nullptr;
}

template <typename T>
Node<T>* SearchMethods<T>::BreadthFirstSearch(State<T>* _initial, State<T>* _final) {
    QueueSearch<T> qSearch;
    vector<Action<T>*> actions;
    return SearchMethods<T>::Search(_initial, _final, qSearch, actions);
}

template <typename T>
Node<T>* SearchMethods<T>::DepthFirstSearch(State<T>* _initial, State<T>* _final) {
    StackSearch<T> sSearch;
    vector<Action<T>*> actions;
    return SearchMethods<T>::Search(_initial, _final, sSearch, actions);
}

#endif
