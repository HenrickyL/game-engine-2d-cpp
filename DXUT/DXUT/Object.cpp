#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de vari�veis est�ticas da classe

Window	*&Object::window	= Engine::window;           // ponteiro para a janela
Input	*&Object::input		= Engine::input;        // tempo do �ltimo quadro
float	&Object::gameTime	= Engine::frameTime;        // tempo do �ltimo quadro


// -------------------------------------------------------------------------------

Object::Object()
{
}

// -------------------------------------------------------------------------------

//Object::~Object()
//{
//	delete _position;
//	delete _sprite;
//}

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
	_sprite->SetPosition(_position);
}

void Object::MoveTo(Position* position)
{
	_position->MoveTo(position);
	_sprite->SetPosition(_position);
};

void Object::MoveTo(Position position)
{
	_position->MoveTo(position);
	_sprite->SetPosition(_position);
};