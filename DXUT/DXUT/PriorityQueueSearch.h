// PriorityQueueSearch.h
#ifndef DXUT_AI_PRIORITY_QUEUE_SEARCH_H
#define DXUT_AI_PRIORITY_QUEUE_SEARCH_H

#include "SearchStructure.h"
#include <queue>
using std::priority_queue;



class PriorityQueueSearch : public SearchStructure {

    struct NodeComparator {
        bool operator()(const Node* a, const Node* b) const {
            return a->Cost() > b->Cost();
        }
    };

private:
    priority_queue<Node*, std::vector<Node*>, NodeComparator> data ;

public:

    void    Push(Node* element) override;
    Node*   Pop() override;
    bool    IsEmpty() const override;
    bool    Exist(const Node* element) const override;
    bool    ExistLargeThan(Node* element) const;
    void    RemoveLargeThanBy(Node* element);

};

#endif
