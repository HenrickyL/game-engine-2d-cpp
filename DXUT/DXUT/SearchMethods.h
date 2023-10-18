#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_METHODS_H

#include "SearchStructure.h"
#include "PriorityQueueSearch.h"
#include "QueueSearch.h"
#include "StackSearch.h"
#include "Node.h"
#include "State.h"
#include "Action.h"
#include "Dictionary.h"
#include <vector>
#include <queue>
using std::vector;
using std::queue;

template <typename T>
class SearchMethods {
private:
    static const int _MAX = 5000;

    static Node<T>* Search(State<T>* initial, State<T>* _final, SearchStructure<T>& edge,  SearchStructure<T>& method, vector<Action<T>*> actions) {
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
    static void DeleteNodes(vector<Node<T>*>& nodesToRemove, Dictionary<T>* controlGenerated) {
        bool deleteIn = controlGenerated != nullptr;
        for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); it++) {
            Node<T>* node = *it;
            if (node) {
                /*if (deleteIn) {
                    controlGenerated->Remove(node->Value());
                }*/
                delete node;
            }
        }
    }
    static void DeleteNotInPath(vector<Node<T>*>& nodesToRemove, Node<T>* path) {
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
    static bool existInVector(vector<Node<T>*> list, const Node<T>* element) {
        for (const auto* item : list) {
            if (item->Equal(element)) return true;
        }
        return false;
    }
    static Node<T>* SearchAndHandleResult(Node<T>* node, State<T>* target, vector<Node<T>*> AllNodes, Dictionary<T>* controlGenerated) {
        DeleteNotInPath(AllNodes, node);
        DeleteNodes(AllNodes, controlGenerated);
        return node->ReversePath();
    }

public:
    static Node<T>* BreadthFirstSearch(State<T>* _initial, State<T>* _final) {
        QueueSearch<T> qSearch;
        vector<Action<T>*> actions;
        return SearchMethods<T>::Search(_initial, _final, qSearch, actions);
    }
    static Node<T>* DepthFirstSearch(State<T>* _initial, State<T>* _final) {
        StackSearch<T> sSearch;
        vector<Action<T>*> actions;
        return SearchMethods<T>::Search(_initial, _final, sSearch, actions);
    }
    static Node<T>* HeuristicSearch(State<T>* _initial, State<T>* _final, vector<Action<T>*> actions, Dictionary<T>* controlGenerated) {
        int count = 0;
        Node<T>* node = new Node<T>(_initial, _final, nullptr);
        T key = _initial->Value();
        if (controlGenerated && !controlGenerated->Contains(key)) {
            controlGenerated->Add(key, _initial);
        }
        PriorityQueueSearch<T> edge;
        edge.Push(node);

        vector<Node<T>*> read;
        vector<Node<T>*> AllNodes;
        AllNodes.push_back(node);

        while (!edge.IsEmpty()) {
            node = edge.Pop();
            count++;

            if (node->GetState()->Equal(_final)) {
                return SearchMethods<T>::SearchAndHandleResult(node, _final, AllNodes, controlGenerated);
            }

            if (node->IsGeneratedPossible() && !actions.empty()) {
                node->GenerateTransitions(actions,_final, controlGenerated);
            }

            read.push_back(node);

            for (Transition<T>* elem : *node->GetState()->Edges()) {
                Node<T>* chield = new Node<T>(elem, _final, node);
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
                        return SearchMethods<T>::SearchAndHandleResult(chield, _final, AllNodes, controlGenerated);
                    }
                }
            }
        }
        DeleteNodes(AllNodes, controlGenerated);
        return nullptr;
    }
};

#endif
