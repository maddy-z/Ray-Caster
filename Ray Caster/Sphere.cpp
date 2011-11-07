#include <math.h>

#include "Sphere.h"
#include "vector.h"
#include "hit.h"
#include "ray.h"

bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{
	Vec3f delta = center - r.getOrigin();
	float distance = delta.Length();
	if (distance <= radius)                                       // if camera is inside the sphere ~
		return false;

	float cos_angle = r.getDirection().Dot3(delta) / distance;
	if (cos_angle <= 0.0f)                                        // Thus, t is smaller than 0
		return false;

	float angle = acos(cos_angle);
	float min_d = sin(angle) * distance;
	if (min_d >= radius)
		return false;

	float tp = sqrt(distance * distance - min_d * min_d), td = sqrt(radius * radius - min_d * min_d);
	float t = tp - td;

	Vec3f dir = r.getDirection(), interPoint = r.getOrigin();
	dir.Scale(t, t, t); interPoint += dir;
	if (t < h.getT())
		h.set(t, NULL, interPoint - center, r);

	return true;
}