#include "Player.h"
// ---------------------------------------------------------------------------------
#include "Breakout.h"
// ---------------------------------------------------------------------------------

Player::Player(Image* img)
{
	_position = new Position();
	this->SetSprite(new Sprite(img));
	_speedMagnitude = 500;
	this->SetSpeed(Vector(Vector::Right * _speedMagnitude));
	_sprite->SetLayer(Layer::MIDDLE);


	// estado inicial do jogo
	state = STOPED;
	// tipo do objeto
	type = PLAYER;
	_sprite->SetFilterColor(Vector(1, 0, 0));
	BBox(_sprite->GetRect());
}
// ---------------------------------------------------------------------------------
Player::~Player()
{
	delete _position;
	delete _sprite;
	delete _bbox;
}
// ---------------------------------------------------------------------------------

void Player::Update()
{
	// inicia o jogo com barra de espaço
	if (state == STOPED && input->KeyDown(VK_SPACE))
		state = PLAYING;

	// desloca jogador horizontalmente
	if (input->KeyDown(VK_RIGHT) && this->Right() <= window->Width()) {
		_speed = (Vector::Right) * _speedMagnitude;
		Translate(_speed * gameTime);
	}
	if (input->KeyDown(VK_LEFT) && this->Left() >= 0) {
		_speed = (Vector::Left)*_speedMagnitude;
		Translate(_speed * gameTime);
	}

}

void Player::OnCollision(Object* obj) {

}

