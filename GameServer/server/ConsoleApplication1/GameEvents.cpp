#include "GameEvents.h"


GameEvents::GameEvents(int type)
{
	_event_type = type;
}


GameEvents::~GameEvents()
{
}

int GameEvents::getType()
{
	return _event_type;
}
