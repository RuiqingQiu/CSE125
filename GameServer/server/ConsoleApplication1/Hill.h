#pragma once
#include <random>
#include <time.h>
#include <math.h>
class Hill
{
private:
	int x, z;
	int width;
	int radius;
	int goldInc;
public:
	Hill(int,int,int, int, int);
	~Hill();

	void update();
	int getX();
	int getZ();
	int getRadius();
	int inHill(int, int);
};

