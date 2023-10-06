#ifndef DXUT_AI_SEARCH_STRUCTURE_H
#define DXUT_AI_SEARCH_STRUCTURE_H
//------------------------------------------
#include "Node.h"
//------------------------------------------
template<typename T>
class SearchStructure {
public:
    virtual void    Push(Node<T>* element) = 0;
    virtual Node<T>*   Pop() = 0;
    virtual bool    IsEmpty() const = 0;
    virtual bool    Exist(const Node<T>* element) const = 0;
};

#endif