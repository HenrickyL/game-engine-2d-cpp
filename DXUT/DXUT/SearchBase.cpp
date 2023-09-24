#include "SearchBase.h"
//------------------------------------------
#include "Transition.h"
#include "QueueSearch.h"
#include <vector>
using std::vector;
#include <queue>
using std::queue;
//------------------------------------------


bool existInVector(vector<Node*> list, Node* element) {
	for (const auto* item : list) {
		if (item == element)
			return true;
	}
	return false;
}

void DeleteNotInPath(vector<Node*>& nodesToRemove, Node* path) {
	queue<Node*> q;
	Node* node = path;
	while (node != nullptr) {
		q.push(node);
		node = node->Father();
	}
	while (!q.empty()) {
		node = q.front();
		q.pop();
		for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); it++) {
			Node* item = *it;
			if (item == node) {
				nodesToRemove.erase(it);
				break;
			}
		}
	}

}

void DeleteNodes(vector<Node*>& nodesToRemove) {
	for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); it++) {
		delete *it;
	}
}

//------------------------------------------

Node* SearchBase::Search(State* initial, State* _final, SearchStructure& edge)
{
	Node* node = new Node(initial, nullptr);
	//borda
	//SearchStructure<Node*>& edge
	edge.Push(node);
	//lidos
	vector<Node*> read;

	vector<Node*> AllNodes;
	AllNodes.push_back(node);

	while (!edge.IsEmpty()) {
		node = edge.Pop();
		read.push_back(node);

		if (node->GetState() == _final) {
			return node;
		}
		for (Transition* elem : *node->GetState()->Edges()) {
			Node* chield = new Node(elem, node);
			AllNodes.push_back(chield);
			if (!existInVector(read, chield) && !edge.Exist(chield)) {
				if (chield->GetState() == _final) {
					DeleteNotInPath(AllNodes, chield);
					DeleteNodes(AllNodes);
					return chield;
				}
				edge.Push(chield);
			}
		}
	}
	DeleteNodes(AllNodes);
	return nullptr;
}

//------------------------------------------

Node* SearchBase::BreadthFirstSearch(State* _initial, State* _final) {
	QueueSearch qSearch;
	return SearchBase::Search(_initial, _final, qSearch);
}
