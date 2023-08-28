#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include <sstream>
using std::stringstream;

class WinApp : public Game
{
private:
	HDC hdc;
	int xi, yi, xf, yf;
	float vxi = 1;
	float vyi = 1;
	float vxf = 1;
	float vyf = 1;
	float a;

	int lastX, lastY;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif