#include "Game.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window* & Game::window = Engine::window;		// ponteiro para a janela
Input* Game::input = Engine::input;					// ponteiro para a entrada
float& Game::gameTime = Engine::frameTime;		// tempo do �ltimo quadro

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
	MessageBox(nullptr, "Paused", "GameStatus", MB_OK);
	Sleep(10);
}

void Game::OnResume()
{
}

// --