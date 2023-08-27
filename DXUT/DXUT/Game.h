#ifndef DXUT_GAME_H
#define DXUT_GAME_H

#include "Window.h"
#include "Input.h"

class Game {
protected:
	static Window* & window;					// janela
	static Input* input;						// entrada
	static float& gameTime;						// tempo do �ltimo quadro
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
};
// ---------------------------------------------------------------------------------
#endif