#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include "DXUT_2D.h"
using std::stringstream;

class WinApp : public Game
{
private:
    Sprite* pause = nullptr;
	Sprite* backg = nullptr;
	Sprite* title = nullptr;

    void OnPause();                     // pausa do jogo
	void InputVerifyExit();

public:
	static Scene* scene;

    WinApp();
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif