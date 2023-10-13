#ifndef DXUT_AI_QUEUE_SEARCH_H
#define DXUT_AI_QUEUE_SEARCH_H

#include "SearchStructure.h"
#include "Node.h"
#include <queue>
using std::queue;

template<typename T>
class QueueSearch : public SearchStructure<T> {
private:
    queue<Node<T>*> data;

public:
    void Push(Node<T>* element) override {
        data.push(element);
    }
    Node<T>* Pop() override {
        Node<T>* element = data.front();
        data.pop();
        return element;
    }
    bool IsEmpty() const override {
        return data.empty();
    }
    bool Exist(const Node<T>* element) const override {
        queue<Node<T>*> tempData = data;
        while (!tempData.empty()) {
            if (tempData.front() == element) {
                    return true;
            }
            tempData.pop();
        }
        return false;
    }
};


#endif
