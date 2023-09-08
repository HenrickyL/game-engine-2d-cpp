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
	bbox = nullptr;
}

// -------------------------------------------------------------------------------

void Object::BBox(Geometry* bb)
{
	if (bbox)
		delete bbox;

	bbox = bb;
	bbox->Translate(Vector(_position->X(), _position->Y()));
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
	if (bbox)
		bbox->Translate(delta);
}

void Object::MoveTo(Position* position)
{
	_position->MoveTo(position);
	if (_sprite)
		_sprite->SetPosition(_position);
};

void Object::MoveTo(Position position)
{
	_position->MoveTo(position);
	if (_sprite)
		_sprite->SetPosition(_position);
	if (bbox)
		bbox->MoveTo(position);
};
// -------------------------------------------------------------------------------
void Object::OnCollision(Object* obj)
{
}