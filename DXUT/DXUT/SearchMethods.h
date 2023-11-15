#ifndef DXUT_AI_SEARCH_METHODS_H
#define DXUT_AI_SEARCH_METHODS_H

#include "SearchStructure.h"

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

    static Node<T>* Search(State<T>* initial, State<T>* _final, SearchStructure<T>& edge, SearchStructure<T>& method, vector<Action<T>*> actions);
    static void DeleteNodes(vector<Node<T>*>& nodesToRemove, Dictionary<T>* controlGenerated);
    static void DeleteNotInPath(vector<Node<T>*>& nodesToRemove, Node<T>* path);
    static bool existInVector(vector<Node<T>*> list, const Node<T>* element);
    static Node<T>* SearchAndHandleResult(Node<T>* node, State<T>* target, vector<Node<T>*> AllNodes, Dictionary<T>* controlGenerated);

public:
    static Node<T>* BreadthFirstSearch(State<T>* _initial, State<T>* _final);
    static Node<T>* DepthFirstSearch(State<T>* _initial, State<T>* _final);
    static Node<T>* HeuristicSearch(State<T>* _initial, State<T>* _final, vector<Action<T>*> actions, Dictionary<T>* controlGenerated, GenerateType generateType, bool useMinCost = true);
};
#include "SearchMethods.inl"
#endif
