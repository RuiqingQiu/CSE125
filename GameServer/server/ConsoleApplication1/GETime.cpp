#include "GETime.h"


GETime::GETime(int t) : GameEvents(2)
{
	if (t >= 0)
		time = t;
	else time = 0;
}


GETime::~GETime()
{
}




void GETime::to_string(std::string& s){

	s += std::to_string(_event_type);
	s += " ";
	s += std::to_string(time);

	//std::cout << "to string:"<< s << "end"<< std::endl;
}