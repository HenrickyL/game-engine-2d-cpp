#ifndef DXUT_GAME_OBJECT_SHANK_H
#define DXUT_GAME_OBJECT_SHANK_H

// ---------------------------------------------------------------------------------
#include "DXUT_2D.h"            
// ---------------------------------------------------------------------------------
class Shank : public Object
{
private:
    Sprite* sprite;


    void InputCharacter();

public:
    Shank();
    ~Shank();

    void Update();
    void Draw();
};

#endif
