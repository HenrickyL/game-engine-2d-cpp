//#include "SearchMethods.h"

#include "PriorityQueueSearch.h"
#include "QueueSearch.h"
#include "StackSearch.h"

template<typename T>
static Node<T>* SearchMethods<T>::BreadthFirstSearch(State<T>* _initial, State<T>* _final) {
    QueueSearch<T> qSearch;
    vector<Action<T>*> actions;
    return SearchMethods<T>::Search(_initial, _final, qSearch, actions);
}


template<typename T>
Node<T>* SearchMethods<T>::DepthFirstSearch(State<T>* _initial, State<T>* _final) {
    StackSearch<T> sSearch;
    vector<Action<T>*> actions;
    return SearchMethods<T>::Search(_initial, _final, sSearch, actions);
}

template<typename T>
Node<T>* SearchMethods<T>::HeuristicSearch(State<T>* _initial, State<T>* _final, vector<Action<T>*> actions, Dictionary<T>* controlGenerated, GenerateType generateType, bool useMinCost) {
    int count = 0;
    Node<T>* node = new Node<T>(_initial, _final, nullptr);
    T key = _initial->Value();
    if (controlGenerated && !controlGenerated->Contains(key)) {
        controlGenerated->Add(key, _initial);
    }
    PriorityQueueSearch<T> edge(useMinCost);
    edge.Push(node);

    vector<Node<T>*> read;
    vector<Node<T>*> AllNodes;
    AllNodes.push_back(node);

    while (!edge.IsEmpty()) {
        node = edge.Pop();
        T value = node->Value();
        std::string res = node->GetPath();
        count++;

        if (node->GetState()->Equal(_final)) {
            return SearchMethods<T>::SearchAndHandleResult(node, _final, AllNodes, controlGenerated);
        }
        if (count > SearchMethods<T>::_MAX) {
            return SearchMethods<T>::SearchAndHandleResult(node, _final, AllNodes, controlGenerated);
        }

        if (!actions.empty()) {
            node->GenerateTransitions(actions, _final, controlGenerated, generateType);
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
            }
            
        }
    }
    DeleteNodes(AllNodes, controlGenerated);
    return nullptr;
}


template<typename T>
Node<T>* SearchMethods<T>::Search(State<T>* initial, State<T>* _final, SearchStructure<T>& edge, SearchStructure<T>& method, vector<Action<T>*> actions) {
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

template<typename T>
void SearchMethods<T>::DeleteNodes(vector<Node<T>*>& nodesToRemove, Dictionary<T>* controlGenerated) {
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

template<typename T>
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


template<typename T>
bool SearchMethods<T>::existInVector(vector<Node<T>*> list, const Node<T>* element) {
    for (const Node<T>* item : list) {
        if (item->Equal(element)) return true;
    }
    return false;
}

template<typename T>
Node<T>* SearchMethods<T>::SearchAndHandleResult(Node<T>* node, State<T>* target, vector<Node<T>*> AllNodes, Dictionary<T>* controlGenerated) {
    DeleteNotInPath(AllNodes, node);
    DeleteNodes(AllNodes, controlGenerated);
    return node->ReversePath();
}
