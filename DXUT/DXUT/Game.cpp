#include "Game.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window*		& Game::window = Engine::window;		// ponteiro para a janela
Input		*Game::input = Engine::input;				// ponteiro para a entrada
Renderer	*Game::renderer = Engine::renderer;				// ponteiro para a entrada
Timer		Game::timer;                      // medidor de tempo


float& Game::gameTime = Engine::frameTime;		// tempo do último quadro

// -------------------------------------------------------------------------------
Game::Game()
{
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------

void Game::OnPause()
{
	Sleep(50);
	
}

void Game::OnResume()
{

}

// --