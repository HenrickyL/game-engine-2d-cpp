#include "Game.h"
#include "Engine.h"
// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window* Game::window = nullptr;		// ponteiro para a janela
Input* Game::input = nullptr;		// ponteiro para a entrada

// -------------------------------------------------------------------------------
Game::Game()
{
	if (!window)
	{
		// ATENÇÃO: assume que a instância da engine é  
		// criada antes da instância da aplicação
		window = Engine::window;
		input = Engine::input;
	}
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// --