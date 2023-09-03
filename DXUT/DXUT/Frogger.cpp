#include "Frogger.h"
// ---------------------------------------------------------------------------------
Frogger::Frogger()
{
    _sprite = new Sprite("Resources/frog.png");
	initX = window->CenterX() - _sprite->Width() / 2.0f;
	initY = 545.0f;
	_sprite->SetAnchor(_sprite->Width() / 2, _sprite->Height() / 2);
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
		_sprite->SetRotation(N);
	}
	else if (input->KeyPress(VK_DOWN) && IsValidPosition(x, y + _jumpDistance))
	{
		Translate(0.0f, _jumpDistance);
		_sprite->SetRotation(S);
	}
	else if (input->KeyPress(VK_LEFT) && IsValidPosition(x-_jumpDistance, y))
	{
		Translate(-_jumpDistance, 0);
		_sprite->SetRotation(W);
	}
	else if (input->KeyPress(VK_RIGHT) && IsValidPosition(x + _jumpDistance, y))
	{
		Translate(_jumpDistance, 0);
		_sprite->SetRotation(E);
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

	if(input->KeyPress(SPACE))
	{
		rotation = (Direction)((rotation + 1)%8);
		_sprite->SetRotation(rotation);

	}
	
}


void Frogger::InWatter() {
	_sprite->SetImage("Resources/frog_watter.png");
}
void Frogger::InFloor() {
	_sprite->SetImage("Resources/frog.png");
}
void Frogger::IsDie() {
	_sprite->SetImage("Resources/frog_die.png");
}