#ifndef DXUT_AI_PRIORITY_QUEUE_SEARCH_H
#define DXUT_AI_PRIORITY_QUEUE_SEARCH_H

#include "SearchStructure.h"
#include "Node.h"
#include <queue>
using std::priority_queue;

template<typename T>
class PriorityQueueSearch : public SearchStructure<T> {

    struct NodeComparator {
        bool operator()(const Node<T>* a, const Node<T>* b) const {
            return a->Cost() > b->Cost();
        }
    };

private:
    priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> data;

public:

    void        Push(Node<T>* element) override;
    Node<T>*    Pop() override;
    bool        IsEmpty() const override;
    bool        Exist(const Node<T>* element) const override;
    bool        ExistLargeThan(Node<T>* element) const;
    void        RemoveLargeThanBy(Node<T>* element);

};

#include "PriorityQueueSearch.inl"

#endif
