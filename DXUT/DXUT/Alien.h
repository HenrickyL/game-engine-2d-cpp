#ifndef _GALAGA_ALIEN_H_
#define _GALAGA_ALIEN_H_

// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
// ---------------------------------------------------------------------------------

class Alien : public Object
{
private:
    float _speedScalar = 80.0f;
public:
    Alien(Image* img);
    ~Alien();

    void Update();

    void SetDirection(const Vector& direction);
};

// ---------------------------------------------------------------------------------
#endif