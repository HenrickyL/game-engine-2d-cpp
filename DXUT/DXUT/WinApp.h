#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include "DXUT_2D.h"
#include "Shank.h"

using std::stringstream;

class WinApp : public Game
{
private:
	Image	* img	= nullptr;        // imagem do logotipo
	Sprite	* backg = nullptr;        // sprite para fundo da cena
	Sprite	* logo1 = nullptr;        // sprite do logotipo
	Sprite	* logo2 = nullptr;        // sprite do logotipo
	Shank	* shank = nullptr;        // objeto do personagem shank


	void InputVerifyExit();

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif