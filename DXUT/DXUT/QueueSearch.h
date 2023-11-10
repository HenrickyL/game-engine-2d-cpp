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
    void Push(Node<T>* element) override;
    Node<T>* Pop() override;
    bool IsEmpty() const override;
    bool Exist(const Node<T>* element) const override;
};

#include "QueueSearch.inl"
#endif
