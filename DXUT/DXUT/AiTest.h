#ifndef _BREAKOUT_H
#define _BREAKOUT_H

#include "DXUT_2D.h"
#include "DXUT_IA.h"
#include <vector>
using std::vector;
class AiTest : public Game
{
private:
	bool viewScene = true;
	bool viewBBox = false;
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;

	vector<State*> states;
	// --------------------------
	Image* imgPlayer = nullptr;
	Image* imgResult = nullptr;

	// --------------------------


	void OnPause();
	void InputVerifyExit();

public:
	static Scene* scene;
	AiTest();

	void Init();
	void Update();
	void Draw();
	void Finalize();
	void Reset();
};
#endif