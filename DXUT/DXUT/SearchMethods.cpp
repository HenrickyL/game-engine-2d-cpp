#include "SearchMethods.h"
//------------------------------------------
#include "Transition.h"
#include "QueueSearch.h"
#include "StackSearch.h"
#include "PriorityQueueSearch.h"
#include <vector>
using std::vector;
#include <queue>
using std::queue;
//------------------------------------------


bool existInVector(vector<Node*> list, const Node* element) {
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
		if(*it)
			delete *it;
	}
}

//------------------------------------------

Node* SearchMethods::Search(State* initial, State* _final, SearchStructure& edge)
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
		/*if (node->GetState() == _final) {
			return node;
		}*/
		read.push_back(node);
		for (Transition* elem : *node->GetState()->Edges()) {
			Node* chield = new Node(elem, node);
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

//------------------------------------------

Node* SearchMethods::SearchAndHandleResult(Node* node, State* target, vector<Node*> AllNodes) {
	DeleteNotInPath(AllNodes, node);
	DeleteNodes(AllNodes);
	return node;
}

//------------------------------------------

Node* SearchMethods::HeuristicSearch(State* initial, State* _final)
{
	Node* node = new Node(initial, nullptr);
	//borda
	//SearchStructure<Node*>& edge
	PriorityQueueSearch edge;
	edge.Push(node);
	//lidos
	vector<Node*> read;

	vector<Node*> AllNodes;
	AllNodes.push_back(node);

	while (!edge.IsEmpty()) {
		node = edge.Pop();

		if (node->GetState() == _final) {
			return SearchMethods::SearchAndHandleResult(node, _final, AllNodes);
		}
		read.push_back(node);
		for (Transition* elem : *node->GetState()->Edges()) {
			Node* chield = new Node(elem, node);
			AllNodes.push_back(chield);
			//pointer exist
			if (!existInVector(read, chield) && !edge.Exist(chield)) {
				edge.Push(chield);
			}
			else if (edge.ExistLargeThan(chield)) {
				edge.RemoveLargeThanBy(chield);
				edge.Push(chield);
			}
		}
	}
	DeleteNodes(AllNodes);
	return nullptr;
}

//------------------------------------------

Node* SearchMethods::BreadthFirstSearch(State* _initial, State* _final) {
	QueueSearch qSearch;
	return SearchMethods::Search(_initial, _final, qSearch);
}

Node* SearchMethods::DepthFirstSearch(State* _initial, State* _final) {
	StackSearch sSearch;
	return SearchMethods::Search(_initial, _final, sSearch);
}
