#ifndef DXUT_AI_QUEUE_SEARCH_H
#define DXUT_AI_SEARCH_STRUCTURE_H
//------------------------------------------
#include "SearchStructure .h"
//------------------------------------------

template <typename T>
class QueueSearch  : public  SearchStructure <T>{
public:
    void Push(const T& element) override;
    T Pop() override;
    bool IsEmpty() const override;
    bool Exist(const T& element) const override;
};

#endif