#include "GEHillUpdate.h"
#include <iostream>

GEHillUpdate::GEHillUpdate(int xx, int zz, int radius):
GameEvents(8)
{
	x = xx;
	z = zz;
	r = radius;
}


GEHillUpdate::~GEHillUpdate()
{
}

void GEHillUpdate::to_string(std::string &s)
{
	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(x);
	s += " ";
	s += "0 ";
	s += std::to_string(z);
	s += " ";
	s += std::to_string(r);
	std::cout << " hill x z r:" << x << " , " << z << " , " << r << std::endl;
}