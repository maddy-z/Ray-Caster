#include <assert.h>

#include "Object3D.h"
#include "Group.h"

class Object3D;

Group::Group(int num) : objs_num(num)
{
	if (num == 0) {
		objs = NULL;
		return;
	}

	assert (num > 0);
	objs = new Object3D*[num];
}

Group::~Group()
{
	if (objs != NULL)
		delete [] objs;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin)
{
	bool iFlag = false;

	for (int i = 0; i < objs_num; ++i) {
		if (objs[i]->intersect(r, h, tmin) == true)
			iFlag = true;
	}

	return iFlag;
}

void Group::addObject(int index, Object3D *obj)
{
	assert (index >= 0 && index < objs_num);

	/*
	Object3D **old = objs;
	objs = new Object3D*[++objs_num];
	
	for (int i = 0; i < index; ++i) { objs[i] = old[i]; }
	for (int i = index; i < objs_num-1; ++i) { objs[i+1] = old[i]; }

	objs[index] = obj;
	*/

	objs[index] = obj;
	return;
}