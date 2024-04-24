#ifndef _MissionariesCannibalsProblem_H
#define _MissionariesCannibalsProblem_H

#include "DXUT_2D.h"
#include "DXUT_IA.h"

#include "MCS.h"

class MissionariesCannibalsProblem : public Game, private Agent<MCS>{
private:
	int numMissionaries = 3;
	int numCannibals = 3;
	bool viewScene = true;
	bool viewBBox = false;
	Sprite* pause = nullptr;
	Sprite* backg = nullptr;
	// --------------------------
	Image* imgMissionary = nullptr;
	Image* imgCannibal = nullptr;
	Image* imgBoat = nullptr;

	// --------------------------

	void OnPause();
	void InputVerifyExit();

public:
	static Scene* scene;
	MissionariesCannibalsProblem();

	void Init();
	void Update();
	void Draw();
	void Finalize();

	void Reset();

	void UpdatePositionObj();


	void GenStates() override;

};

#endif