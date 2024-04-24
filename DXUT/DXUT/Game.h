#ifndef DXUT_GAME_H
#define DXUT_GAME_H

#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Renderer.h"
#include <string>

class Game {
protected:
	static Window	*& window;					// janela
	static Timer	timer;						//tempo
	static Input	* input;					// entrada
	static Renderer	* renderer;					// entrada

	static float	& gameTime;					// tempo do último quadro

	Sprite* _sptPause = nullptr;
	std::string _name = "GameName";
public:
	Game();										// construtor
	virtual ~Game();							// destrutor

	// Métodos que podem ser sobrescritos para implementar 
	// funcionalidade específica para o jogo. Eles já possuem
	// uma implementação padrão.

	virtual void OnPause();                     // pausa do jogo
	virtual void OnResume();                    // retoma do jogo
	// Estes métodos são puramente virtuais, isto é, devem ser 
		// implementados em todas as classes derivas de App.

	virtual void Init() = 0;                    // inicialização do jogo
	virtual void Update() = 0;                  // atualização do jogo
	virtual void Draw() = 0;                    // desenho da cena
	virtual void Finalize() = 0;                // finalização do jogo

	std::string Name() const;

};

inline std::string Game::Name() const { return _name; }

// ---------------------------------------------------------------------------------
#endif