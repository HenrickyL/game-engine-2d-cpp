#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include "DXUT_2D.h"
#include "Frogger.h"
#include "Obstacle.h"
#include <list>
using std::list;
using std::stringstream;

class WinApp : public Game
{
private:
    Image* woodSmall = nullptr;                // pequeno tronco de madeira
    Image* woodBig = nullptr;                // grande tronco de madeira
    Image* turtleSmall = nullptr;                // pequena fila de tartarugas
    Image* turtleBig = nullptr;                // grande fila de tartarugas
    Image* truck = nullptr;                // caminhão tanque
    Image* car1 = nullptr;                // carro de passeio azul
    Image* car2 = nullptr;                // carro de passeio branco
    Image* car3 = nullptr;                // carro de passeio amarelo
    Image* car4 = nullptr;                // carro de passeio vermelho

    Sprite* background = nullptr;                // imagem de fundo
    Frogger* frogger = nullptr;                // sapo

    Obstacle* obj = nullptr;                // um obstáculo do jogo

    list<Obstacle*> objects;                      // lista de obstáculos em movimento

	void InputVerifyExit();

public:
    WinApp();
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif