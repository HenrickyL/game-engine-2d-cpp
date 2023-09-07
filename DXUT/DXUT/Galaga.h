#ifndef _GALAGA_H
#define _GALAGA_H

#include "Game.h"
#include "DXUT_2D.h"
using std::stringstream;

class Galaga : public Game
{
private:
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;
	Sprite* title = nullptr;

	Image* alien1Img = nullptr;
	Image* alien2Img = nullptr;
	Image* alien3Img = nullptr;
	Image* alien4Img = nullptr;

	Image* playerImg = nullptr;
	Image* missileImg = nullptr;


	void OnPause();
	void InputVerifyExit();

public:
	static Scene* scene;

	Galaga();
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif