#ifndef DXUT_AI_STACK_SEARCH_H
#define DXUT_AI_STACK_SEARCH_H
//------------------------------------------
#include "SearchStructure.h"
#include<stack>
using std::stack;
//------------------------------------------


class StackSearch : public SearchStructure {
private:
    stack<Node*> data;
public:
    void    Push(Node* element) override;
    Node*   Pop() override;
    bool    IsEmpty() const override;
    bool    Exist(const Node* element) const override;
};

#endif