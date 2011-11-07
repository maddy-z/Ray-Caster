#ifndef _SCENEPARSER_H_
#define _SCENEPARSER_H_

#include <iostream>
using namespace std;

#include "Camera.h"
#include "OrthographicCamera.h"
#include "vector.h"
#include "Group.h"
#include "Sphere.h"

class Object3D;
class Group;
class Camera;
class Sphere;

#define MAX_PARSER_TOKEN_LENGTH 100

// ===============================================================
// ===============================================================

class SceneParser
{

public:
	
	// CONSTRUCTORS, DESTRUCTOR & INITIALIZE
	SceneParser();
	SceneParser(const char *filename);
	~SceneParser();

	// ACCESSORS
	Group* getGroup() { return group; }
	Camera* getCamera() { return camera; }
	Vec3f getBackgroundColor() { return background_color; }

private:

	// HELPER FUNCTIONS
	void initialize();
	int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
	
	void parseFile();
	void parseBackground();
	void parseMaterial();
	void parseOrthographicCamera();

	Object3D* parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
	Group* parseGroup();
	Sphere* parseSphere();
  
	Vec3f readVec3f();
	float readFloat();
	int readInt();

	// REPRESENTATION
	Group *group;
	Camera *camera;
	Vec3f background_color;

	Vec3f current_object_color;
	FILE *file;

};

inline ostream& operator << (ostream& os, SceneParser& sparser)
{
	os << "Scene Parser:" << endl
	   << "\tBackground Color = " << sparser.getBackgroundColor() << endl << endl
	   << *((OrthographicCamera *)(sparser.getCamera())) << endl
	   << *(sparser.getGroup()) << endl;

	return os;
}

// ====================================================================
// ====================================================================

#endif
