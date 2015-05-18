#pragma once
#include <random>
#include <time.h>
#include <math.h>
class Hill
{
private:
	int x, z;
	int radius;
	int goldInc;
public:
	Hill(int,int,int, int);
	~Hill();

	void update(int, int);
	int getX();
	int getZ();
	int inHill(int, int);
};

