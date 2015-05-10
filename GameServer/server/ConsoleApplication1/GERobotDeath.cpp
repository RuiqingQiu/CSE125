#include "GERobotDeath.h"
#include <iostream>


GERobotDeath::GERobotDeath(int c, int k)
	:GameEvents(0)
{
	cid = c;
	kcid = k;
	//TODO: change int
}


GERobotDeath::~GERobotDeath()
{
}


void GERobotDeath::to_string(std::string& s){

	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(cid);
	s += " ";
	s += std::to_string(kcid);
	//std::cout << "to string:"<< s << "end"<< std::endl;
}
