#ifndef _GALAGA_PLAYER_H_
#define _GALAGA_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es
#include "DXUT_2D.h"

// ---------------------------------------------------------------------------------

class Player : public Object
{
public:
    Player(Image* img);
    ~Player();

    void Update();
};

// ---------------------------------------------------------------------------------

#endif