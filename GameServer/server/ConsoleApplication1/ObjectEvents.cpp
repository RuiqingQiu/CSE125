#include "ObjectEvents.h"


ObjectEvents::ObjectEvents(unsigned int type)
{
	_event_type = type;
}


ObjectEvents::~ObjectEvents()
{
}


void ObjectEvents::setName(std::string name)
{
	_name = name;
}


void ObjectEvents::setCid(unsigned int cid)
{
	_cid = cid;
}

unsigned int ObjectEvents::getEvent()
{
	return _event_type;
}
unsigned int ObjectEvents::getCid()
{
	return _cid;
}
std::string ObjectEvents::getName()
{
	return _name;
}