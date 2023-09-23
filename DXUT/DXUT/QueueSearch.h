#ifndef DXUT_AI_QUEUE_SEARCH_H
#define DXUT_AI_QUEUE_SEARCH_H
//------------------------------------------
#include "SearchStructure.h"
#include<queue>
using std::queue;
//------------------------------------------


template <typename T>
class QueueSearch  : public SearchStructure<T>{
private:
    queue<T> data;
public:
    void    Push(const T& element) override;
    T       Pop() override;
    bool    IsEmpty() const override;
    bool    Exist(const T& element) const override;
};

#endif