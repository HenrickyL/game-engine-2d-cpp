#ifndef DXUT_GLCAMERA
#define DXUT_GLCAMERA

#include "Camera.h"
#include "GLWindow.h" //#include <GL/glu.h>

/// TODO: 
/*
	* Usar Frustum Culling para verificar se algo está a vista da camera 
	* Fazer algum forma de algo ser apresentado na vista da camera (UI)
	* Converter Visão da camera para Mundo e vice versa
*/

class GLCamera : public Camera {
public:
	GLCamera(const Window* window);
	GLCamera(const Window* window, const Position& pos);

	void Update() override;
};

#endif