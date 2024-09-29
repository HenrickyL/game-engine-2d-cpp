#ifndef MYCLASS_TEST_H
#define MYCLASS_TEST_H


#include "Game.h"
#include "Geometry.h"
#include "UT_GL.h"
#include "Scene.h"
#include "GLRenderer.h"
#include "GLLight.h"

#include <string.h>
#include <sstream>
#include "GLGroundUI.h"
#include "GLOriginGizmoUI.h"
#include <vector>

#include "Shape3d.h"

using std::vector;
using std::stringstream;


class MyGame : public Game {
private:
	bool useVertexBuffer = false;
	GLCamera* currentCam = nullptr;
	Vector globalRotation = Vector::Zero;
	GLCamera cam = GLCamera(graphics, Position(0, 0.5f, 5));
	GLCamera cam2 = GLCamera(graphics, Position(0, 1.0f, 3));
	GLLight* light = nullptr;

	string s = "";
	GLRenderer* _drawnner3D;
	int onSolid = 0;

	GLGroundUI groundUi = GLGroundUI(100);
	GLOriginGizmoUI wordOrigin;
	
	vector<Shape3D*> shapes;
	Shape3D* current = nullptr;
	int currentIndex = -1;

	vector<Geometry*> geometries;
	Geometry* geo = nullptr;
	int geoIndex = -1;

	void InputRotationGlobal();
	void InputRotationLocal();
	void InputCameraFrustum();

	void InputCamera();
	void InputEnd();

	void InitCircularObjects();

	void Reset();


public:

	void Init() override;
	void Update(double frameTime) override;
	void Draw() override;
	void Finalize() override;
};

#endif
