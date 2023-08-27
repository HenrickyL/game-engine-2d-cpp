#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include <sstream>
using std::stringstream;

class WinApp : public Game
{
private:
	stringstream textSize;
	stringstream textMode;
	stringstream textMouse;
	COLORREF color = RGB(255, 0, 0);
	bool isRight = true;
	float tax = 0.05;
	float increase = 1;
	bool isActivate = false;
	float R = 20;
	float RDefaut = 20;


	int lastX, lastY;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif