#ifndef UT_GAME_MAZE_PROBLEM_H
#define UT_GAME_MAZE_PROBLEM_H

#include "Game.h"

class MazeProblem : public Game {
private:

public:
	void Init() override;
	void Update(double frameTime) override;
	void Draw() override;       
	void Finalize() override;
};
#endif