#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include "Image.h"
#include "Sprite.h"
using std::stringstream;

class WinApp : public Game
{
private:
	Sprite* backg = nullptr;            // sprite do fundo de tela
	Sprite* shank = nullptr;            // sprite do personagem 

	Image* logoImg = nullptr;            // imagem do logotipo
	Sprite* logo1 = nullptr;            // sprite 1 do logotipo
	Sprite* logo2 = nullptr;            // sprite 2 do logotipo

	float x = 0, y = 0;                    // posição x,y do shank

	void InputVerifyExit();
	void InputCharacter();

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif