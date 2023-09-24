#include "StackSearch.h"


void StackSearch::Push(Node* element) {
    data.push(element);
}

Node* StackSearch::Pop() {
    Node* element = data.top();
    data.pop();
    return element;
}

bool StackSearch::IsEmpty() const {
    return data.empty();
}

bool StackSearch::Exist(const Node* element) const {
    stack<Node*> tempData = data;
    while (!tempData.empty()) {
        if (tempData.top() == element) {
            return true;
        }
        tempData.pop();
    }
    return false;
}
