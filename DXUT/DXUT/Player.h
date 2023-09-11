#ifndef _BREAKOUT_PLAYER_H_
#define _BREAKOUT_PLAYER_H_
// ---------------------------------------------------------------------------------
// Inclusões
#include "DXUT_2D.h"
// ---------------------------------------------------------------------------------
enum PLAYERSTATE { PLAYING, STOPED };
// ---------------------------------------------------------------------------------

class Player : public Object
{
private :
    Image* _missile;
public:
    PLAYERSTATE state;
    Player(Image* img);
    ~Player();

    void OnCollision(Object* obj);
    void Update();
};

// ---------------------------------------------------------------------------------

#endif