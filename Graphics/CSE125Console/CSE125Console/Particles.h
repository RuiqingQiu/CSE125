#ifndef CSE167_Particles_h
#define CSE167_Particles_h
#include "stdafx.h"
#include <vector>

typedef struct
{
	//Is particle active?
	bool alive;

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
}
particles;
#endif