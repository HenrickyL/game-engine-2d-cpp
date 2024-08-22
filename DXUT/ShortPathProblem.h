#ifndef _ShortPathProblem_H
#define _ShortPathProblem_H

#include "DXUT_2D.h"
#include "DXUT_IA.h"
#include "DXImage.h"
#include <vector>
using std::vector;
class ShortPathProblem : public Game
{
private:
	bool viewScene = true;
	bool viewBBox = false;
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;
	Sprite* targetLocal = nullptr;


	vector<State<Position>*> states;
	// --------------------------
	DXImage* imgPlayer = nullptr;
	DXImage* imgResult = nullptr;
	DXImage* imgPause = nullptr;
	DXImage* imgBG = nullptr;

	// --------------------------


	void OnPause();
	void InputVerifyExit();

public:
	static Scene* scene;
	ShortPathProblem();

	void Init() override;
	void Update(double frameTime) override;
	void Draw() override;
	void Finalize() override;
	void Reset();
};
#endif