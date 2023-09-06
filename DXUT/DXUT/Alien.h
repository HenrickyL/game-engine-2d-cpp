#ifndef _GALAGA_ALIEN_H_
#define _GALAGA_ALIEN_H_

// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
#include <string>           // string da biblioteca STL
// ---------------------------------------------------------------------------------

class Alien : public Object
{
public:
    Alien(Image* img);
    ~Alien();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------

inline void Alien::Draw()
{
    _sprite->Draw();
}

// ---------------------------------------------------------------------------------
#endif