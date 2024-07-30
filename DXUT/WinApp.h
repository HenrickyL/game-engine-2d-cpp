#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include "DXUT_2D.h"
#include "DXImage.h"
using std::stringstream;

class WinApp : public Game
{
private:
    Sprite* pause = nullptr;
	DXImage* imgPause = nullptr;

    void OnPause();                     // pausa do jogo
	void InputVerifyExit();

public:
    WinApp();
	void Init() override;
	void Update(double delta)override;
	void Draw()override;
	void Finalize()override;
};
#endif