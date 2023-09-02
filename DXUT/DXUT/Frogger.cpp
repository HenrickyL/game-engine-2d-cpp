#include "Frogger.h"
// ---------------------------------------------------------------------------------
Frogger::Frogger()
{
    _sprite = new Sprite("Resources/frog.png");
	initX = window->CenterX() - _sprite->Width() / 2.0f;
	initY = 545.0f;
	Reset();
}

// ---------------------------------------------------------------------------------
void Frogger::Reset()
{
	MoveTo(initX, initY, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Frogger::~Frogger()
{
    delete _sprite;
}

// ---------------------------------------------------------------------------------

void Frogger::InputCharacter()
{
	if(input->KeyPress(VK_UP) && IsValidPosition(x, y-_jumpDistance))
	{
		Translate(0.0f, -_jumpDistance);
	}
	else if (input->KeyPress(VK_DOWN) && IsValidPosition(x, y + _jumpDistance))
	{
		Translate(0.0f, _jumpDistance);
	}
	else if (input->KeyPress(VK_LEFT) && IsValidPosition(x-_jumpDistance, y))
	{
		Translate(-_jumpDistance, 0);
	}
	else if (input->KeyPress(VK_RIGHT) && IsValidPosition(x + _jumpDistance, y))
	{
		Translate(_jumpDistance, 0);
	}


}

bool Frogger::IsValidPosition(float newX, float newY)
{
	if( (0 <= newX && newX <= window->Width()) &&
		(60 <= newY && newY <= 545))
	{
		return true;
	}
	return false;
}



void Frogger::Update()
{
	if (input->KeyPress(KEY_R))
	{
		Reset();
	}
	InputCharacter();
	
}
