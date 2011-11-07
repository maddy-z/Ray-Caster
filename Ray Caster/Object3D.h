#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "vector.h"

class Ray;
class Hit;

// =================================================
// =================================================

class Object3D
{

public:
	Object3D(Vec3f c = Vec3f(1.0f, 1.0f, 1.0f)): color(c) {}
	virtual ~Object3D() {}

	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

	void setColor(Vec3f c) { color = c; }
	Vec3f getColor() const { return color; }

protected:
	Vec3f color;

};

#endif