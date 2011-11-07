#ifndef _ORTHOGRAPHICCAMERA_H_
#define _ORTHOGRAPHICCAMERA_H_

#include <iostream>
using namespace std;

#include <assert.h>

#include "Camera.h"
#include "vector.h"

class OrthographicCamera : public Camera
{
	friend ostream& operator << (ostream&, OrthographicCamera&);

public:
	OrthographicCamera( Vec3f c = Vec3f(0.0f, 0.0f, 0.0f), 
						Vec3f pro = Vec3f(0.0f, 0.0f, 1.0f),
						Vec3f u = Vec3f(0.0f, 1.0f, 0.0f),
						int s = 10) : center(c), direction(pro), up(u), size(s) 
	{ 
		assert (size > 0);
		assert (!(direction[0] == 0.0f && direction[1] == 0.0f && direction[2] == 0.0f));

		initialize(); 
	}

	virtual ~OrthographicCamera() {}

	virtual Ray generateRay(const Vec2f &point);

	int getSize() const { return size; }

private:
	// Initialization Function
	void initialize();

	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;

	int size;
	
};

inline ostream& operator << (ostream &os,  OrthographicCamera &ogCamera)
{
	os << "OrthographicCamera:" << endl 
	   << "\tCenter = "			<< ogCamera.center << endl 
	   << "\tDirection = "		<< ogCamera.direction << endl
	   << "\tUp = "				<< ogCamera.up << endl
	   << "\tSize = "			<< ogCamera.size << endl;

	return os;
}

#endif