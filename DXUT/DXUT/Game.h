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

	static float	& gameTime;					// tempo do �ltimo quadro

	Sprite* _sptPause = nullptr;
	std::string _name = "GameName";
public:
	Game();										// construtor
	virtual ~Game();							// destrutor

	// M�todos que podem ser sobrescritos para implementar 
	// funcionalidade espec�fica para o jogo. Eles j� possuem
	// uma implementa��o padr�o.

	virtual void OnPause();                     // pausa do jogo
	virtual void OnResume();                    // retoma do jogo
	// Estes m�todos s�o puramente virtuais, isto �, devem ser 
		// implementados em todas as classes derivas de App.

	virtual void Init() = 0;                    // inicializa��o do jogo
	virtual void Update() = 0;                  // atualiza��o do jogo
	virtual void Draw() = 0;                    // desenho da cena
	virtual void Finalize() = 0;                // finaliza��o do jogo

	std::string Name() const;

};

inline std::string Game::Name() const { return _name; }

// ---------------------------------------------------------------------------------
#endif