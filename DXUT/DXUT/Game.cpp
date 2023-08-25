#include "Game.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window* Game::window = nullptr;		// ponteiro para a janela
Input* Game::input = nullptr;		// ponteiro para a entrada
float& Game::gameTime = Engine::frameTime;    // tempo do �ltimo quadro

// -------------------------------------------------------------------------------
Game::Game()
{
	if (!window)
	{
		// ATEN��O: assume que a inst�ncia da engine �  
		// criada antes da inst�ncia da aplica��o
		window = Engine::window;
		input = Engine::input;
	}
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------

void Game::OnPause()
{
	Sleep(10);
}

// --