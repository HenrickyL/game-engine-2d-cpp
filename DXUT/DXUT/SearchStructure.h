#ifndef DXUT_AI_SEARCH_STRUCTURE_H
#define DXUT_AI_SEARCH_STRUCTURE_H
//------------------------------------------
#include "Node.h"
//------------------------------------------

class SearchStructure {
public:
    virtual void    Push(Node* element) = 0;
    virtual Node*   Pop() = 0;
    virtual bool    IsEmpty() const = 0;
    virtual bool    Exist(const Node* element) const = 0;
};

#endif