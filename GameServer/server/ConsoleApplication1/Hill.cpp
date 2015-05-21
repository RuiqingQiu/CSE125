#include "Hill.h"


Hill::Hill(int xx, int zz, int w, int rr, int gold)
{
	x = xx;
	z = zz;
	width = w;
	radius = rr;
	goldInc = gold;
	srand(time(NULL));
}


Hill::~Hill()
{

}

void Hill::update()
{
	int newX = rand()%(width/2-radius)*((rand()%2) ? 1: -1);
	int newZ = rand() % (width/2-radius)*((rand() % 2) ? 1 : -1);
	x = newX;
    z = newZ;
}

int Hill::getX()
{
	return x;
}


int Hill::getZ()
{
	return z;
}

int Hill::inHill(int xx, int zz)
{
	return (sqrt((xx-x)*(xx-x) + (zz-z)*(zz-z)) <= radius) ? goldInc : 0;
}

int Hill::getRadius()
{
	return radius;
}