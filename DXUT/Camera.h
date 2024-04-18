#ifndef DX_UT_CAMERA_H
#define DX_UT_CAMERA_H

#include "Movable.h"
class Camera : public Movable {
protected:
	Position _pointOfView = Position::Zero;
	Vector _orientation = Vector::Down;
public:
	Camera();
	Camera(const Position& pos);


	virtual void LookAt(const Position& pos);
	virtual void TranslateLookAt(const Vector& delta);
	virtual Position pointOfView()const;

	// Métodos para controlar a orientação da câmera
	virtual void SetOrientation(const Vector& orientation);
	virtual Vector orientation();

	virtual void Update() =0;
	virtual void Draw();
};

#endif