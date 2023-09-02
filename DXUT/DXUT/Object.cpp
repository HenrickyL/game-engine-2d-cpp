#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window	*& Object::window	= Engine::window;           // ponteiro para a janela
Input	*& Object::input	= Engine::input;        // tempo do último quadro
float	& Object::gameTime	= Engine::frameTime;        // tempo do último quadro


// -------------------------------------------------------------------------------

Object::Object() : x(0.0f), y(0.0f), z(0.5f)
{
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------