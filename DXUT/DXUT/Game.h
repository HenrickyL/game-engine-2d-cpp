#ifndef DXUT_GAME_H
#define DXUT_GAME_H

#include "Window.h"
#include "Input.h"

class Game {
protected:
	static Window* window;						// janela
	static Input* input;						// entrada
public:
	Game();										// construtor
	virtual ~Game();								// destrutor

	// Estes métodos são puramente virtuais, isto é, devem ser 
		// implementados em todas as classes derivas de App.

	virtual void Init() = 0;					// inicialização
	virtual void Update() = 0;					// atualização
	virtual void Finalize() = 0;				// finalização	

	// Estes métodos possuem uma implementação vazia por padrão
	// e apenas um deles deve ser sobrescrito na classe derivada:
	// - Draw é executado a cada ciclo do laço principal
	// - Display é chamado apenas uma vez no início da aplicação
	//   e deve ser chamado manualmente em Update toda vez
	//   que a tela precisar ser redesenhada.

	virtual void Draw() {}						// desenho
	virtual void Display() {}					// exibição
	virtual void OnPause() { Sleep(10); }		// em pausa
};
#endif