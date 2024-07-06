#ifndef DX_UT_CAMERA_H
#define DX_UT_CAMERA_H

#include "Movable.h"
#include "Window.h"


//TODO: testar os os valores de forma dinamica
class Camera : public Movable {
private:
	// Configuração da matriz de projeção (simulação) - Frustum Culling
	float _fov = 45.0f;
	float _aspect;
	float _near =0.1f;
	float _far = 10.0f;
	void UpdateAspect();
protected:
	Vector _pointOfView = Vector::Zero;
	Vector _orientation = Vector::Up;
	Vector _direction = Vector::Backward;
	Vector _left = Vector::Left;
	const Window* _window = nullptr;
	virtual void UpdateProjection() const;

	
public:
	Camera(const Window* window);
	Camera(const Window* window, const Position& pos);


	virtual void LookAt(const Vector& pos);
	virtual void TranslateLookAt(const Vector& delta);
	virtual Position pointOfView()const;

	// Métodos para controlar a orientação da câmera
	virtual void SetOrientation(const Vector& orientation);
	virtual Vector orientation()const;

	virtual void SetDirection(const Vector& orientation);
	virtual Vector direction()const;

	virtual Vector left()const;

	virtual void Update() =0;
	virtual void Draw();
	virtual void Reset();



	float fov()const;
	float aspect()const;
	float zNear()const;
	float zFar()const;

	void SetFov(float value);
	void SetNear(float value);
	void SetFar(float value);

};

#endif