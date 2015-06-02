#pragma once
#include <random>
#include <time.h>
#include <math.h>
#include "GOBox.h"

#define NUM_OF_PARTICLES 25
class Hill
{
private:
	int x, z;
	int field_width;
	int field_height;
	int radius;
	int goldInc;
	int index;
	std::vector<GameObj*> particles;
	btVector3 locations[13];

public:
	Hill(int,int,int, int, int,int);
	~Hill();

	void update();
	int getX();
	int getZ();
	int getRadius();
	int inHill(int, int);

	void createParticles(std::vector<GameObj*>* gameObjs);
	void updateParticles();
};

