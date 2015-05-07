#include "stdafx.h"
#include "EventSystem.h"
#include "EventInfo.h"
#include "EventDeath.h"
EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::ProcessGamePacket(GameInfoPacket* packet)
{
	vector<EventInfo*>eventinfos =  packet->event_infos;
	for (int i = 0; i < eventinfos.size(); i++)
	{
		EventInfo* event = eventinfos[i];
		if (typeid(event) == typeid(EventInfo*))
		{
			printf("Death Event has been received \n");
		}
	}
}