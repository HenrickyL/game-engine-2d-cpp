#ifndef DXUT_HASHEABLE_H
#define DXUT_HASHEABLE_H

#include <cstddef>
class Hasheable {
public:
    virtual std::size_t customHash() const = 0;
    virtual bool operator==(const Hasheable& outra) const = 0;
    virtual ~Hasheable() {}
};

//// Implementação de um operador de igualdade global para comparar objetos Hasheable
//bool operator==(const Hasheable& a, const Hasheable& b) {
//    return a.customHash() == b.customHash();
//}

#endif