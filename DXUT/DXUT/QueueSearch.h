#ifndef DXUT_AI_QUEUE_SEARCH_H
#define DXUT_AI_QUEUE_SEARCH_H
//------------------------------------------
#include "SearchStructure.h"
#include<queue>
using std::queue;
//------------------------------------------


class QueueSearch  : public SearchStructure{
private:
    queue<Node*> data;
public:
    void    Push(Node* element) override;
    Node*   Pop() override;
    bool    IsEmpty() const override;
    bool    Exist(const Node* element) const override;
};

#endif