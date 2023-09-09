#ifndef _BREAKOUT_H
#define _BREAKOUT_H

#include "DXUT_2D.h"


enum ObjTypes
{
	PLAYER,
	BALL,
	BLOCK
};


class Breakout : public Game
{
private:
	bool viewScene = true;
	bool viewBBox = false;
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;

	Image* playerImg = nullptr;


	void OnPause();
	void InputVerifyExit();

public:
	static Scene* scene;

	Breakout();
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif