#ifndef DXUT_AI_SEARCH_STRUCTURE_H
#define DXUT_AI_SEARCH_STRUCTURE_H
//------------------------------------------


template <typename T>
class SearchStructure {
public:
    virtual void Push(const T& element) = 0;
    virtual T Pop() = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool Exist(const T& element) const = 0;
};

#endif