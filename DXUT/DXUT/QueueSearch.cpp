#include "QueueSearch.h"

template <typename T>
void QueueSearch<T>::Push(const T& element) {
    data.push(element);
}

template <typename T>
T QueueSearch<T>::Pop() {
    T element = data.front();
    data.pop();
    return element;
}

template <typename T>
bool QueueSearch<T>::IsEmpty() const {
    return data.empty();
}

template <typename T>
bool QueueSearch<T>::Exist(const T& element) const {
    std::queue<T> tempData = data;
    while (!tempData.empty()) {
        if (tempData.front() == element) {
            return true;
        }
        tempData.pop();
    }
    return false;
}
