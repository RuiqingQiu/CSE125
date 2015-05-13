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

#include "Window.h"
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
		std::cout << "mydoubleptr points to " << typeid(*event).name() << '\n';
		switch (event->event_type){
		case TEventDeath:{
							 printf("Death Event has been received \n");
							 //Switch back to game view
							 Window::factory->switchView('1');
							 //Explosion particle effect
							 //Explosion sound
							 break;
		}
		case TEventParticle:{
								printf("particle event received \n");
								//Window::factory->battlemode->PushGeoNode();
								break;
		}
		case TEventTimer:{
							 printf("time event received \n");
							 //Change variable in build mode and battle mode
							 break;


		}
		case TEventScoreboard:{
								  printf("scoreboard event received\n");
								  //Change score variables in battle mode and build mode
								  break;

		}
		case TEventUpdateHealth:{
									printf("health event received\n");
									//Update health bar
									break;

		}
		case TEventCollisionHappen:{
									   printf("collision event received\n");
									   //Collision sound
									   break;

		}
		case TEventWaiting:{
							   printf("waiting event received\n");
							   break;

		}
		case TEventEmergency:{
								 printf("emergency event received\n");
								 break;

		}
		case TEventDefault:{
							   printf("Event default, should not entered\n");
							   break;

		}

		}
	}
}