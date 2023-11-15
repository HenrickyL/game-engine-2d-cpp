#ifndef MCOBJ_H
#define MCOBJ_H

#include "Object.h"
#include "Image.h"
class MCObj : public Object {
private:

public:

	MCObj(Image* img, float scale = 0.15f);
	void Update() override;
};

#endif