#ifndef _FROGGER_OBSTACLE_H_
#define _FROGGER_OBSTACLE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "DXUT_2D.h"

// ---------------------------------------------------------------------------------

class Obstacle : public Object
{
private:
    Sprite* _sprite;
    float initX = 0, initY = 0;

public:
    Obstacle(Image* img, float speed);
    ~Obstacle();

    void Update();
    void Draw();

    int Width() const;
    int Height() const;

    void SetInitialPosition(float x, float y);
    void Reset();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline int Obstacle::Width() const
{
    return _sprite->Width();
}

inline int Obstacle::Height() const
{
    return _sprite->Height();
}
inline void Obstacle::Draw()
{    _sprite->Draw(x, y, Layer::UPPER);}
// ---------------------------------------------------------------------------------

#endif