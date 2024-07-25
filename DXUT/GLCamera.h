#ifndef DXUT_GLCAMERA
#define DXUT_GLCAMERA

#include "Camera.h"
#include "GLWindow.h" //#include <GL/glu.h>
#include "GLDrawableBase.h"
#include "Frustum.h"
/// TODO: 
/*
	* Usar Frustum Culling para verificar se algo está a vista da camera 
	* Fazer algum forma de algo ser apresentado na vista da camera (UI)
	* Converter Visão da camera para Mundo e vice versa
*/

class GLCamera : public Camera, public GLDrawableBase {
private:
	Frustum _frustum;
	bool _useFrustum = false;

	void CalculeDirection();
	void TranslateTo(const Vector& delta) override;
	void UpdateFrustum();
	void DrawFrustum() const;
	void UpdateProjection() const override;



public:
	GLCamera(const Graphics* graphic);
	GLCamera(const Graphics* graphic, const Position& pos);


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


	bool IsInFrustum(const Position& position, float radius) const;
};

#endif