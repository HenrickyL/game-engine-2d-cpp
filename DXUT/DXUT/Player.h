#ifndef _GALAGA_PLAYER_H_
#define _GALAGA_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões
#include "DXUT_2D.h"

// ---------------------------------------------------------------------------------

class Player : public Object
{
private :
    Image* _missile;
public:
    Player(Image* imgPlayer, Image* missileImg);
    ~Player();

    void Update();
};

// ---------------------------------------------------------------------------------

#endif