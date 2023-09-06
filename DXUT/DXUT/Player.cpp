#include "Player.h"
// ---------------------------------------------------------------------------------

Player::Player(Image* img)
{
	_position = new Point();
	this->SetSprite(new Sprite(img));
	this->SetSpeed(Vector::Right * 160.0f);
	_sprite->SetLayer(Layer::MIDDLE);
}
// ---------------------------------------------------------------------------------
Player::~Player()
{
	delete _position;
	delete _sprite;
}
// ---------------------------------------------------------------------------------

void Player::Update()
{
	if(input->KeyDown(VK_LEFT))
	{
		if (_speed <=> Vector::Right)
			_speed = _speed * -1;

		if(_position->X() - _sprite->HalfWidth() > 0)
			this->Translate(_speed * gameTime);

	}
	if(input->KeyDown(VK_RIGHT))
	{
		if (_speed <=> Vector::Left)
			_speed = _speed * -1;

		if (_position->X() + _sprite->HalfWidth() <= window->Width())
			this->Translate(_speed * gameTime);
	}
}

