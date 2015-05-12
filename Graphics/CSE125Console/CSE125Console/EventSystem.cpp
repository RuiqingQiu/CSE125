#include "stdafx.h"
#include "EventSystem.h"
#include "EventInfo.h"
#include "EventDeath.h"
#include "EventParticle.h"
#include "EventTimer.h"
#include "EventScoreboard.h"
#include "EventHealth.h"
#include "EventCollision.h"
#include "EventWaiting.h"
#include "EventEmergency.h"

EventSystem::EventSystem()
{
}


EventSystem::~EventSystem()
{
}

void EventSystem::ProcessGamePacket(GameInfoPacket* packet)
{
	vector<EventInfo*>eventinfos = packet->event_infos;
	for (int i = 0; i < eventinfos.size(); i++)
	{
		EventInfo* event = eventinfos[i];
		if (typeid(event) == typeid(EventDeath*))
		{
			printf("Death Event has been received \n");
		}
		else if (typeid(event) == typeid(EventParticle*))
		{
			printf("particle event received \n");
		}
		else if (typeid(event) == typeid(EventTimer*)){
			printf("time event received \n");
		}
		else if (typeid(event) == typeid(EventScoreboard*)){
			printf("scoreboard event received\n");
		}
		else if (typeid(event) == typeid(EventHealth*)){
			printf("health event received\n");
		}
		else if (typeid(event) == typeid(EventCollision*)){
			printf("collision event received\n");
		}
		else if (typeid(event) == typeid(EventWaiting*)){
			printf("waiting event received\n");
		}
		else if (typeid(event) == typeid(EventEmergency*)){
			printf("emergency event received\n");
		}
	}
}