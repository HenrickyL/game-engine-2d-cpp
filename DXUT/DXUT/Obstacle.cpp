#include "Obstacle.h"
// ---------------------------------------------------------------------------------
Obstacle::Obstacle(Image* img, float speed)
{
    sprite = new Sprite(img);
    SetSpeed(speed);
}

// ---------------------------------------------------------------------------------

Obstacle::~Obstacle()
{
    delete sprite;
}
// ---------------------------------------------------------------------------------
void Obstacle::Update()
{
    // objeto caminha no eixo x
    Translate(-Speed() * gameTime, 0.0f);

    // passa objeto de um lado da tela para o outro
    if (int(x) + sprite->Width() < 0)
        MoveTo(float(window->Width() + sprite->Width()), y);
}