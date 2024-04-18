#ifndef DXUT_GLCAMERA
#define DXUT_GLCAMERA

#include "Camera.h"
#include "GLWindow.h" //#include <GL/glu.h>

class GLCamera : public Camera {
public:
	GLCamera();
	GLCamera(const Position& pos);

	void Update() override;
};

#endif