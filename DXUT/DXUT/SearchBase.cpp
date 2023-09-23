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


Node* SearchBase::BFS(State* initial, State* _final)
{
	Node* node = new Node(initial, nullptr);
	//borda
	queue<Node*> edge;
	//lidos
	vector<Node*> read;

	while (!edge.empty()) {
		node = edge.front();
		read.push_back(node);


		if (node->GetState() == _final) {
			return node;
		}
		for (Transition* elem : *node->GetState()->Edges()) {
			Node* chield = new Node(elem, node);
			if (!existInVector(read, chield) && !ExistInQueue(edge, chield)) {
				if (chield->GetState() == _final) {
					return chield;
				}
			}
		}
	}
	return nullptr;
}