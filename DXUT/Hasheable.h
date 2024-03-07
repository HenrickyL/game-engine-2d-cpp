#ifndef DXUT_HASHEABLE_H
#define DXUT_HASHEABLE_H

#include <cstddef>
#include <functional>

class Hasheable {
public:
    virtual std::size_t customHash() const = 0;
    virtual bool operator==(const Hasheable& outra) const = 0;
    virtual ~Hasheable() {}
};

#endif