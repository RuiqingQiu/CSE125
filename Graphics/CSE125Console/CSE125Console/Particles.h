#ifndef CSE167_Particles_h
#define CSE167_Particles_h
#include "stdafx.h"
#include <vector>

typedef struct
{
	//Is particle active?
	bool alive;
	bool up;
	bool right;
	bool in;

	//Particle's time to live
	float life;

	//Alpha val
	float fade;
	
	//Color
	float r;
	float g;
	float b;

	//Position
	float x ;
	float y ;
	float z ;

	//Velocity
	float xi;
	float yi;
	float zi;

	//scale
	float sx;
	float sy;
	float sz;

	//rotation
	float rx;
	float ry;
	float rz;

	//alpha
	float alpha;

	//speed
	float speed;
}
particles;
#endif