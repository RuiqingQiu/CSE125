#include "GERobotDeath.h"
#include <iostream>


GERobotDeath::GERobotDeath(int c)
	:GameEvents(0)
{
	cid = c;
	//TODO: change int
}


GERobotDeath::~GERobotDeath()
{
}


void GERobotDeath::to_string(std::string& s){

	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(cid);
	std::cout << "to string:"<< s << "end"<< std::endl;
}
