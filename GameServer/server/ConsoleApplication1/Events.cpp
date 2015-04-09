#include "Events.h"


Events::Events(unsigned int type)
{
	_event_type = type;
}


Events::~Events()
{
}


void Events::setName(std::string name)
{
	_name = name;
}


void Events::setCid(unsigned int cid)
{
	_cid = cid;
}

unsigned int Events::getEvent()
{
	return _event_type;
}
unsigned int Events::getCid()
{
	return _cid;
}
std::string Events::getName()
{
	return _name;
}