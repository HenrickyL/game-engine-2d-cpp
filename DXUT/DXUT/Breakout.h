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
	static Breakout* instance;
	bool viewScene = true;
	bool viewBBox = false;
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;

	// --------------------------
	Image* tile1 = nullptr;           // bloco verde
	Image* tile2 = nullptr;           // bloco cinza
	Image* tile3 = nullptr;           // bloco vermelho
	Image* tile4 = nullptr;           // bloco roxo
	Image* tile5 = nullptr;           // bloco amarelo
	// --------------------------

	Image* playerImg = nullptr;
	Image* ballImg = nullptr;


	void OnPause();
	void InputVerifyExit();

	Breakout();
public:
	static Scene* scene;

	void Init();
	void Update();
	void Draw();
	void Finalize();
	void Reset();

	static Breakout* Instance();
};
#endif