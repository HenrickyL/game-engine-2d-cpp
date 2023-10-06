#ifndef DXUT_AI_STACK_SEARCH_INL
#define DXUT_AI_STACK_SEARCH_INL

template<typename T>
void StackSearch<T>::Push(Node<T>* element) {
    data.push(element);
}

template<typename T>
Node<T>* StackSearch<T>::Pop() {
    Node<T>* element = data.top();
    data.pop();
    return element;
}

template<typename T>
bool StackSearch<T>::IsEmpty() const {
    return data.empty();
}

template<typename T>
bool StackSearch<T>::Exist(const Node<T>* element) const {
    stack<Node<T>*> tempData = data;
    while (!tempData.empty()) {
        if (tempData.top() == element) {
            return true;
        }
        tempData.pop();
    }
    return false;
}

#endif
