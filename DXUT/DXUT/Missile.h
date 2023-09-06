#ifndef _GALAGA_MISSILE_H_
#define _GALAGA_MISSILE_H_
// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
// ---------------------------------------------------------------------------------
class Missile : public Object
{
public:
    Missile(Image* img);
    ~Missile();

    void Update() override;
};
 

#endif