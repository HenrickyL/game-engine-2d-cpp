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
    void Push(Node<T>* element) override;
    Node<T>* Pop() override;
    bool IsEmpty() const override;
    bool Exist(const Node<T>* element) const override;
};

#include "StackSearch.inl"

#endif
