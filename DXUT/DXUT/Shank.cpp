#include "Shank.h"
// ---------------------------------------------------------------------------------


Shank::Shank()
{
	sprite = new Sprite("Resources/Shank.png");
	MoveTo(80.0f, 90.0f, Layer::MIDDLE);
}
Shank::~Shank()
{
	delete sprite;
}

void Shank::InputCharacter()
{
    float tax = 1.5f;
    if (input->KeyDown(VK_LEFT))
        x -= 50.0f * gameTime;
    if (input->KeyDown(VK_RIGHT))
        x += 50.0f * gameTime;
    if (input->KeyDown(VK_UP))
        y -= 50.0f * gameTime;
    if (input->KeyDown(VK_DOWN))
        y += 50.0f * gameTime;
}


void Shank::Update()
{
    InputCharacter();
}
void Shank::Draw()
{
    sprite->Draw(x, y, z);
}