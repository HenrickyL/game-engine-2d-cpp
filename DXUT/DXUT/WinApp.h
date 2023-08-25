#ifndef DXUT_WINAPP_H
#define DXUT_WINAPP_H

#include "App.h"
#include <sstream>
using std::stringstream;

class WinApp : public App
{
private:
	stringstream textSize;
	stringstream textMode;
	stringstream textMouse;

	int lastX, lastY;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};
#endif