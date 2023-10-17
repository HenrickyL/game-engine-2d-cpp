#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window	*&Object::window	= Engine::window;           // ponteiro para a janela
Input	*&Object::input		= Engine::input;        // tempo do último quadro
float	&Object::gameTime	= Engine::frameTime;        // tempo do último quadro


// -------------------------------------------------------------------------------

Object::Object()
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
	_bbox->Translate(Vector(_position->X(), _position->Y()));
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
		_sprite->SetPosition(_position);
	}
}

// -------------------------------------------------------------------------------

void Object::Translate(const Vector& delta)
{
	_position->Translate(delta);
	if(_sprite)
		_sprite->SetPosition(_position);
	if (_bbox)
		_bbox->Translate(delta);
}

void Object::MoveTo(Position* position)
{
	_position->MoveTo(position);
	if (_sprite)
		_sprite->SetPosition(_position);
	if (_bbox)
		_bbox->MoveTo(_position);
};

void Object::MoveTo(Position position)
{
	_position->MoveTo(position);
	if (_sprite)
		_sprite->SetPosition(_position);
	if (_bbox)
		_bbox->MoveTo(_position);
};
// -------------------------------------------------------------------------------
void Object::OnCollision(Object* obj)
{
}