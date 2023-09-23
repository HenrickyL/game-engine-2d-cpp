#include "SearchBase.h"
#include <queue>
#include <vector>
#include "Transition.h"
using std::queue;
using std::vector;

bool existInVector(vector<Node*> list, Node* element) {
	for (const auto* item : list) {
		if (item == element)
			return true;
	}
	return false;
}


bool ExistInQueue(queue<Node*> _queue, Node* element) {
	bool result = false;
	Node* node;
	//remove all elements and search
	while (!_queue.empty()) {
		node = _queue.front();
		_queue.pop();
		if (!result && node == element) {
			return true;
		}
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


Node* SearchBase::BFS(State* initial, State* _final)
{
	Node* node = new Node(initial, nullptr);
	//borda
	queue<Node*> edge;
	edge.push(node);
	//lidos
	vector<Node*> read;

	vector<Node*> AllNodes;
	AllNodes.push_back(node);

	while (!edge.empty()) {
		node = edge.front();
		edge.pop();
		read.push_back(node);

		if (node->GetState() == _final) {
			return node;
		}
		for (Transition* elem : *node->GetState()->Edges()) {
			Node* chield = new Node(elem, node);
			AllNodes.push_back(chield);
			if (!existInVector(read, chield) && !ExistInQueue(edge, chield)) {
				if (chield->GetState() == _final) {
					DeleteNotInPath(AllNodes, chield);
					DeleteNodes(AllNodes);
					return chield;
				}
				edge.push(chield);
			}
		}
	}
	return nullptr;
}