#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window	*&Object::window	= Engine::window;           // ponteiro para a janela
float	&Object::gameTime	= Engine::_frameTime;        // tempo do último quadro


// -------------------------------------------------------------------------------

Object::Object(): Movable(Position::Zero)
{
	//tipo do objeto
	type = 0;
	// bounding box do objeto
	_bbox = nullptr;
}

//Object::~Object()
//{
//	if(_position) delete _position;
//	if(_sprite) delete _sprite;
//	if(_bbox) delete _bbox;
//}

// -------------------------------------------------------------------------------

void Object::BBox(Geometry* bb)
{
	if (_bbox)
		delete _bbox;

	_bbox = bb;
	_bbox->TranslateTo(Vector(position().x(), position().y()));
}
// -------------------------------------------------------------------------------

void Object::Draw()
{
	if(_sprite != nullptr)
		_sprite->Draw();
}


// -------------------------------------------------------------------------------

void Object::SetSprite(Sprite* sprite)
{
	if(_sprite != sprite)
	{
		_sprite = sprite;
		_sprite->MoveTo(position());
	}
}

// -------------------------------------------------------------------------------

void Object::TranslateTo(const Vector& delta)
{
	this->TranslateTo(delta);
	if(this->_sprite)
		_sprite->MoveTo(position());
	if (this->_bbox)
		_bbox->TranslateTo(delta);
}

void Object::MoveTo(Position* pos)
{
	this->MoveTo(pos);
	if (_sprite)
		_sprite->MoveTo(pos);
	if (_bbox)
		_bbox->MoveTo(pos);
};

void Object::MoveTo(const Position& pos)
{
	this->MoveTo(pos);
	if (_sprite)
		_sprite->MoveTo(pos);
	if (_bbox)
		_bbox->MoveTo(pos);
};
// -------------------------------------------------------------------------------
void Object::OnCollision(Object* obj)
{
}