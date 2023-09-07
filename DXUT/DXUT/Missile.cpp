#include "Missile.h"

// ---------------------------------------------------------------------------------
#include "Galaga.h"
// ---------------------------------------------------------------------------------

Missile::Missile(Image* img)
{
	_position = new Point();
	SetSprite(new Sprite(img));
	SetSpeed(Vector::Up * 250.0f);
	_sprite->SetLayer(Layer::UPPER);
}
// ---------------------------------------------------------------------------------

Missile::~Missile()
{
	delete _sprite;
	delete _position;
}
// ---------------------------------------------------------------------------------

void Missile::Update()
{
	Translate(_speed * gameTime);
	if(_position->Y() < 0)
	{
		Galaga::scene->Remove();
	}
}
// ---------------------------------------------------------------------------------
