#include <assert.h>
#include <math.h>

#include "vector.h"
#include "OrthographicCamera.h"
#include "ray.h"

// ===========================================================
// ===========================================================

/*
Ray OrthographicCamera::generateRay(const Vec2f &point)
{
	assert (point[0] >= 0.0f && point[0] <= 1.0f);
	assert (point[1] >= 0.0f && point[1] <= 1.0f);

	float hScale = size * (point.x() - 0.5f), uScale = size * (point.y() - 0.5);
	Vec3f h = horizontal, u = up;
	h.Scale(hScale, hScale, hScale); u.Scale(uScale, uScale, uScale);
	Vec3f origin = center + h + u;
	
	Ray r(direction, origin);
	return r;
}


void OrthographicCamera::initialize()
{
	direction.Normalize();

	float temp = direction.Dot3(up);
	if (temp > 1e-6 && temp < (-1) * 1e-6) {                     // if not ortho to direction vector ~~
		if (direction.x() != 0.0f) {
			float x = (-1) * direction.y() / direction.x();
			up.Set(x, 1.0f, 0.0f);
		}
		else if (direction.y() != 0.0f) {
			float y = (-1) * direction.z() / direction.y();
			up.Set(0.0f, y, 1.0f);
		}
		else if (direction.z() != 0.0f) {
			float z = (-1) * direction.y() / direction.z();
			up.Set(0.0f, 1.0f, z);
		}
	}		// Finish orthoing to the direction vector ~~~
	up.Normalize();

	Vec3f::Cross3(horizontal, direction, up);
	horizontal.Normalize();

	return;
}
*/


Ray OrthographicCamera::generateRay ( const Vec2f & point )

{

	assert (point[0] >= 0.0f && point[0] <= 1.0f);
	assert (point[1] >= 0.0f && point[1] <= 1.0f);

	float hScale = size * (point.x() - 0.5f), uScale = size * (point.y() - 0.5);
	Vec3f h = horizontal, u = up;
	h.Normalize(); u.Normalize();

	u.Scale(uScale, uScale, uScale); 
	h.Scale(hScale, hScale, hScale);

	Vec3f origin = center + h + u;
	
	Ray r(direction, origin);
	return r;

}


void OrthographicCamera::initialize()
{
	direction.Normalize();
	up.Normalize();

	float temp = direction.Dot3(up);
	if (temp > 1e-6 || temp < (-1) * 1e-6)                        // if not ortho to direction vector ~~
	{
		std::cout << "WARNING:\tCamera's Up Vector is not orthogonal to Direction Vector." << endl;
		std::cout << "Start to adjust Camera's Up Vector" << endl;

		Vec3f::Cross3 ( horizontal, direction, up );
		horizontal.Normalize();

		Vec3f::Cross3 ( up, horizontal, direction );
		up.Normalize();

		std::cout << "End adjusting Camera's Up Vector" << endl;

		return;
	}																// Finish orthoing to the direction vector ~~~

	Vec3f::Cross3(horizontal, direction, up);
	horizontal.Normalize();

	return;

}