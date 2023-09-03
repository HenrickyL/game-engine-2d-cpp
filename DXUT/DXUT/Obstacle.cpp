#include "Obstacle.h"
// ---------------------------------------------------------------------------------
Obstacle::Obstacle(Image* img, float speed)
{
    _sprite = new Sprite(img);
    SetSpeed(speed);
}

// ---------------------------------------------------------------------------------

Obstacle::~Obstacle()
{
    delete _sprite;
}
// ---------------------------------------------------------------------------------
void Obstacle::Update()
{
    // objeto caminha no eixo x
    Translate(-Speed() * gameTime, 0.0f);

    // passa objeto de um lado da tela para o outro
    if (int(x) + _sprite->Width() < 0)
        MoveTo(float(window->Width() + _sprite->Width()), y);
}
// ---------------------------------------------------------------------------------

void Obstacle::SetInitialPosition(float x, float y)
{
    initX = x; initY = y;
    Reset();
}


void Obstacle::Reset()
{
    MoveTo(initX, initY);
}
