#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "ray.h"

class Vec2f;

// ==============================================
// ==============================================

class Camera
{

public:
	Camera() {}
	virtual ~Camera() {}

	// Pure Virtual Function
	virtual Ray generateRay(const Vec2f &point) = 0;

private:

};

#endif