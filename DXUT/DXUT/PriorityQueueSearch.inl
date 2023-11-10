//#include "PriorityQueueSearch.h"


template<typename T>
PriorityQueueSearch<T>::PriorityQueueSearch(bool _useMinPriority) : useMinPriority(_useMinPriority) {
    NodeComparator nodeComparator;
    nodeComparator.pqSearch = this;
    data = priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator>(nodeComparator);
}

template<typename T>
void PriorityQueueSearch<T>::Push(Node<T>* element){
    data.push(element);
}


template<typename T>
Node<T>* PriorityQueueSearch<T>::Pop() {
    Node<T>* element = data.top();
    data.pop();
    return element;
}
template<typename T>
bool  PriorityQueueSearch<T>::IsEmpty() const {
    return data.empty();
}

template<typename T>
bool  PriorityQueueSearch<T>::Exist(const Node<T>* element) const {
    priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> tempData = data;
    while (!tempData.empty()) {
        if (tempData.top()->Equal(element)) {
            return true;
        }
        tempData.pop();
    }
    return false;
}

template<typename T>
bool PriorityQueueSearch<T>::ExistLargeThan(Node<T>* element) const {
    priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> tempData = data;
    while (!tempData.empty()) {
        Node<T>* top = tempData.top();
        if (top->GetState()->Equal(element->GetState()) && top->Cost() > element->Cost()) {
            return true;
        }
        tempData.pop();
    }
    return false;
}

template<typename T>
void PriorityQueueSearch<T>::RemoveLargeThanBy(Node<T>* element) {
    vector<Node<T>*> newNodes;
    while (!data.empty()) {
        Node<T>* node = data.top();
        data.pop();

        if (node->GetState() == element->GetState() && node->Cost() < element->Cost()) {
            //node->DeletePath();
            //delete node;
            break;
        }
        newNodes.push_back(node);
    }

    for (Node<T>* node : newNodes) {
        data.push(node);
    }
}