#pragma once
#include <random>
#include <time.h>
#include <math.h>
#include "GOBox.h"

#define NUM_OF_PARTICLES 50
class Hill
{
private:
	int x, z;
	int field_width;
	int field_height;
	int radius;
	int goldInc;
	std::vector<GameObj*> particles;

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

