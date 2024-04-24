#include "MCObj.h"


MCObj::MCObj(Image* img, float scale) {
	_position = new Position();
	this->SetSprite(new Sprite(img));
	_magnitude = 100;
	_sprite->SetLayer(Layer::MIDDLE);
	_sprite->SetScale(scale);

	BBox(_sprite->GetCircle());
}


void MCObj::Update() {

}
