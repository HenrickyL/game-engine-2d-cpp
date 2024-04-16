#ifndef DX_UT_CAMERA_H
#define DX_UT_CAMERA_H

#include "Movable.h"
class Camera : public Movable {
public:
	Camera();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif