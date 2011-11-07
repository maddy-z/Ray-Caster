#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <assert.h>
#include "Object3D.h"
#include "vector.h"

class Sphere : public Object3D
{

public:
	Sphere( Vec3f c, float r = 1.0f, Vec3f color = Vec3f(1.0f, 1.0f, 1.0f)): 
			Object3D(color), 
			center(c), 
			radius(r) 
	{ assert (r > 0); }
	
	virtual ~Sphere() {}

	virtual bool intersect(const Ray &r, Hit &h, float min);

	Vec3f getCenter() const { return center; }
	float getRadius() const { return radius; }

	void setCenter(Vec3f c) { center = c; }
	void setRadius(float r) { radius = r; }

private:
	Vec3f center;
	float radius;

};

inline ostream& operator << (ostream& os, Sphere& s)
{
	os << "Sphere:\n" << "\tCenter = " << s.getCenter() << endl
					  << "\tRadius = " << s.getRadius() << endl
					  << "\tColor = " << s.getColor() << endl;
	return os;
}

#endif