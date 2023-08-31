#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "Game.h"
#include <sstream>
using std::stringstream;

class WinApp : public Game
{
private:
	int lastX, lastY;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif