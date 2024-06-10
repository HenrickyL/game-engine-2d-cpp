#ifndef DXUT_GLCAMERA
#define DXUT_GLCAMERA

#include "Camera.h"
#include "GLWindow.h" //#include <GL/glu.h>
#include "GLDrawableBase.h"
/// TODO: 
/*
	* Usar Frustum Culling para verificar se algo está a vista da camera 
	* Fazer algum forma de algo ser apresentado na vista da camera (UI)
	* Converter Visão da camera para Mundo e vice versa
*/

class GLCamera : public Camera, public GLDrawableBase {
private:
	Vector _direction = Vector::Backward;
	Vector _left = Vector::Left;
	void CalculeDirection();
	void TranslateTo(const Vector& delta) override;

public:
	GLCamera(const Window* window);
	GLCamera(const Window* window, const Position& pos);

	void Update() override;
	void LookAt(const Vector& pos) override;
	void RotateBy(const Vector& delta) override;
	void RotateTo(const Vector& delta) override;

	void TranslateLeft(float speed);
	void TranslateRight(float speed);
	void TranslateForward(float speed);
	void TranslateBackward(float speed);
	void TranslateUp(float speed);
	void TranslateDown(float speed);


	
	void MoveTo(const Position& position) override;

	void Reset() override;

	virtual void Draw() override;
};

#endif