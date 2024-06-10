#include "MCObj.h"


MCObj::MCObj(Image* img, float scale) {
	this->MoveTo(Position::Zero);
	this->SetSprite(new Sprite(img));
	this->SetMagnitude(100);
	_sprite->SetLayer(Layer::MIDDLE);
	_sprite->SetScale(scale);

	BBox(_sprite->GetCircle());
}


void MCObj::Update() {

}
