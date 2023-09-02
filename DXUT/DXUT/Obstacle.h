#ifndef _FROGGER_OBSTACLE_H_
#define _FROGGER_OBSTACLE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "DXUT_2D.h"

// ---------------------------------------------------------------------------------

class Obstacle : public Object
{
private:
    Sprite* sprite;
    

public:
    Obstacle(Image* img, float speed);
    ~Obstacle();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Obstacle::Draw()
{    sprite->Draw(x, y, z);}
// ---------------------------------------------------------------------------------

#endif