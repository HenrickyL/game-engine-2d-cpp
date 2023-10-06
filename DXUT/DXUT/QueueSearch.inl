#ifndef DXUT_AI_QUEUE_SEARCH_INL
#define DXUT_AI_QUEUE_SEARCH_INL

#include "Node.h"


template<typename T>
void QueueSearch<T>::Push(Node<T>* element) {
    data.push(element);
}

template<typename T>
Node<T>* QueueSearch<T>::Pop() {
    Node<T>* element = data.front();
    data.pop();
    return element;
}

template<typename T>
bool QueueSearch<T>::IsEmpty() const {
    return data.empty();
}

template<typename T>
bool QueueSearch<T>::Exist(const Node<T>* element) const {
    queue<Node<T>*> tempData = data;
    while (!tempData.empty()) {
        if (tempData.front() == element) {oi
            return true;
        }
        tempData.pop();
    }
    return false;
}

#endif
