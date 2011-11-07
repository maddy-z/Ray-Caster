#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cfloat>

#include "Object3D.h"
#include "OrthographicCamera.h"
#include "Scene_parser.h"
#include "Sphere.h"
#include "Group.h"
#include "image.h"
#include "hit.h"
#include "ray.h"


// ======================================================
// Static Global Variables used to parse the arguments ~~
// ======================================================

char *input_file = NULL;
char *output_file = NULL;
char *depth_file = NULL;

int width = 100;
int height = 100;
float depth_min = 0.0f;
float depth_max = FLT_MAX;


// ============================================================
// ============================================================

int main(int argc, char **argv)
{
	// Sample Command Lines:
	// raycast -input input.txt -size 100 100 -output output.tga
	// raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.tga

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-input")) {
			i++; assert (i < argc); 
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-size")) {
			i++; assert (i < argc); 
			width = atoi(argv[i]);
		
			i++; assert (i < argc); 
			height = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) 
		{
			i++; assert (i < argc); 
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-depth")) 
		{
			i++; assert (i < argc);
			depth_min = atof(argv[i]);

			i++; assert (i < argc);
			depth_max = atof(argv[i]);
			// i++; assert (i < argc); 
			// depth_file = argv[i];
		}
		else {
			printf ("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	// Scene Initialization ~~
	SceneParser sparser( input_file );
	
	Image img( width, height ); 
	img.SetAllPixels( Vec3f(0.0f, 0.0f, 0.0f) );
	// img.SetAllPixels( sparser.getBackgroundColor() );
	
	Camera *ogCamera = sparser.getCamera();
	Group *scene = sparser.getGroup();

	// Testing Procedure for SceneParser.
	cout << sparser;

	Vec2f cameraPoint;
	Vec3f normal(0.0f, 1.0f, 0.0f);

	float *depthArray = new float[width * height];
	for (int i = 0; i < width * height; ++i) {
		depthArray[i] = FLT_MIN;
	}

	cout << "Start to Generate Ray" << endl;
	
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			int size = ((OrthographicCamera *)(ogCamera)) -> getSize();
			cameraPoint.Set((float)(i) / (float)(height), (float)(j) / (float)(width));
			
			Hit hitPoint(FLT_MAX, NULL, normal);
			Ray r = ogCamera -> generateRay(cameraPoint);
			if (scene -> intersect(r, hitPoint, FLT_MIN) == true) 
			{
				depthArray[i * width + j] = hitPoint.getT();
				// status[j * width + i] = true;
			}
		}
	}

	float t_min = FLT_MAX, t_max = FLT_MIN;
	for (int i = 0; i < width * height; ++i) {
		if (depthArray[i] == FLT_MIN)
			continue;

		if (depthArray[i] < t_min) t_min = depthArray[i];
		if (depthArray[i] > t_max) t_max = depthArray[i];
	}

	cout << "T Min: " << t_min << endl
		 << "T Max: " << t_max << endl;

	if (depth_min == 0.0f && depth_max == FLT_MAX)
	{
		cout << "Default Mapping" << endl;

		float factor = t_max - t_min;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j) 
			{
				if (depthArray[i * width + j] == FLT_MIN)
					continue;

				depthArray[i * width + j] = 1.0f - (depthArray[i * width + j] - t_min) / factor;
				Vec3f c(depthArray[i * width + j], depthArray[i * width + j], depthArray[i * width + j]);
				img.SetPixel(i, j, c);
			}
		}
	} else {
		cout << "Specified Mapping" << endl;

		float factor = depth_max - depth_min;
		Vec3f white(1.0f, 1.0f, 1.0f), black(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < height; ++i) 
		{
			for (int j = 0; j < width; ++j) 
			{
				if (depthArray[i * width + j] == FLT_MIN)
					continue;
				
				if (depthArray[i * width + j] < depth_min) {
					img.SetPixel(i, j, white);
				}
				else if (depthArray[i * width + j] > depth_max) {
					img.SetPixel(i, j, black);
				}
				else {
					depthArray[i * width + j] = 1.0f - (depthArray[i * width + j] - depth_min) / factor;
					Vec3f c(depthArray[i * width + j], depthArray[i * width + j], depthArray[i * width + j]);
					img.SetPixel(i, j, c);	
				}
			}
		}
	}

	img.SaveTGA(output_file);

	// delete [] status;
	delete [] depthArray;
	return 0;
}