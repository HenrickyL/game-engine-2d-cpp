#ifndef DXUT_AI_STACK_SEARCH_H
#define DXUT_AI_STACK_SEARCH_H

#include "SearchStructure.h"
#include "Node.h"
#include <stack>
using std::stack;

template<typename T>
class StackSearch : public SearchStructure<T> {
private:
    stack<Node<T>*> data;

public:
    void Push(Node<T>* element) override {
        data.push(element);
    }
    Node<T>* Pop() override{
        Node<T>* element = data.top();
        data.pop();
        return element;
    }
    bool IsEmpty() const override {
        return data.empty();
    }
    bool Exist(const Node<T>* element) const override {
        stack<Node<T>*> tempData = data;
        while (!tempData.empty()) {
            if (tempData.top() == element) {
                return true;
            }
            tempData.pop();
        }
        return false;
    }
};



#endif
