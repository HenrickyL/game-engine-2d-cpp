#ifndef MYCLASS_TEST_2D_H
#define MYCLASS_TEST_2D_H


#include "Game.h"
#include "Geometry.h"
#include "GLRenderer.h" 
#include "GLImage.h"
#include "Sprite.h"
#include <vector>

using std::vector;
using std::stringstream;


class Test2D : public Game {
private:
	GLRenderer* _drawnner;
	GLImage* img = nullptr;
	Sprite* sprite = nullptr;
	vector<Geometry*> geometries;
	Vector globalRotation = Vector::Zero;
	Geometry* geo = nullptr;

	void Reset();


public:

	void Init() override;
	void Update(double frameTime) override;
	void Draw() override;
	void Finalize() override;
};

#endif
