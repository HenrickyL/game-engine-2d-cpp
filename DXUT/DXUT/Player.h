#ifndef _BREAKOUT_PLAYER_H_
#define _BREAKOUT_PLAYER_H_
// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"
// ---------------------------------------------------------------------------------
enum PLAYERSTATE { PLAYING, STOPED };
// ---------------------------------------------------------------------------------

class Player : public Object
{
public:
    uint state;                         // estado do jogo

    Player(Image* img);                           // construtor
    ~Player();                          // destrutor

    void OnCollision(Object* obj);     // tratamento de colisão
    void Update();                      // atualização do objeto
};

#endif