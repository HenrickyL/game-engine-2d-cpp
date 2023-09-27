#include "Player.h"
// ------------------------
// ------------------------

Player::Player(Image* img) {
	_position = new Position();
	this->SetSprite(new Sprite(img));
	_magnitude= 100;
	_sprite->SetLayer(Layer::MIDDLE);
	BBox(_sprite->GetCircle());
}


void Player::Update() {
}

void Player::OnCollision(Object* obj) {

}


