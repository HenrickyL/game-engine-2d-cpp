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
	if
}

void Player::OnCollision(Object* obj) {

}


