#ifndef UT_ABSTRACT_LIST_H
#define UT_ABSTRACT_LIST_H

#include <vector>
#include <stdexcept>

template <typename T>
class AbstractList {
protected:
    std::vector<T> _elements;

    virtual ~AbstractList() = default;

    virtual void addElement(T element);
    virtual void removeElement(T element);
    virtual T getElement(size_t index) const;
    virtual size_t getSize() const;
};

#include "AbstractList.inl"

#endif
