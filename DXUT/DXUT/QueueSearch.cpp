#include "QueueSearch.h"


void QueueSearch::Push(Node* element) {
    data.push(element);
}

Node* QueueSearch::Pop() {
    Node* element = data.front();
    data.pop();
    return element;
}

bool QueueSearch::IsEmpty() const {
    return data.empty();
}

bool QueueSearch::Exist(const Node* element) const {
    queue<Node*> tempData = data;
    while (!tempData.empty()) {
        if (tempData.front() == element) {
            return true;
        }
        tempData.pop();
    }
    return false;
}

