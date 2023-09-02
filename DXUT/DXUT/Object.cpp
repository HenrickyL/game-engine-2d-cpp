#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de vari�veis est�ticas da classe

Window	*& Object::window	= Engine::window;           // ponteiro para a janela
Input	*& Object::input	= Engine::input;        // tempo do �ltimo quadro
float	& Object::gameTime	= Engine::frameTime;        // tempo do �ltimo quadro


// -------------------------------------------------------------------------------

Object::Object() : x(0.0f), y(0.0f), z(0.5f)
{
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------