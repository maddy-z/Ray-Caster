#ifndef _GROUP_H_
#define _GROUP_H_

#include <iostream>
using namespace std;

#include "Object3D.h"
#include "Sphere.h"

// ====================================================
// ====================================================

class Group;

class Group : public Object3D
{
	friend ostream & operator << (ostream&, Group&);

public:
	Group(int num = 0);
	virtual ~Group();

	virtual bool intersect(const Ray &r, Hit &h, float tmin);
	void addObject(int index, Object3D *obj);

private:
	int objs_num;
	Object3D **objs;

};

inline ostream& operator << (ostream &os, Group &g)
{
	os << "Group:" << endl
	   << "\tObject Number = " << g.objs_num << endl;
	
	for (int i = 0; i < g.objs_num; ++i)
		os << *((Sphere*)(g.objs[i]));

	return os;
}

#endif