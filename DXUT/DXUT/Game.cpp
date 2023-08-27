#include "Game.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window* & Game::window = Engine::window;		// ponteiro para a janela
Input* Game::input = Engine::input;					// ponteiro para a entrada
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
	MessageBox(nullptr, "Paused", "GameStatus", MB_OK);
	Sleep(10);
}

void Game::OnResume()
{
}

// --