#ifndef MYCLASS_TEST_H
#define MYCLASS_TEST_H


#include "Game.h"
#include "Geometry.h"
#include "GLDrawGeometry.h"
#include "GLCamera.h"
#include <string.h>
#include <sstream>

using std::stringstream;

struct Obj {
	int x = 0;
	int y = 0;
	float z = -25;
};


class MyGame : public Game {
private:
	Geometry* obj;
	Rect* rect;
	GLDrawGeometry drawner;
	GLCamera* cam;
	string s = "";
	float globalRotation = 0;
	std::vector<void (*)(Obj)> functionVector;
	int index = 0;
	Movable* object;

	Window* window;

public:
	void Init() override;
	void Update(double frameTime) override;
	void Draw() override;
	void Finalize() override;
};

#endif
