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
#include "GameCore.h"

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
							 //Switch back to game view
							 if (((EventDeath*)event)->death_id == (g_pCore->pPlayer->playerid)){
								 printf("Death Event has been received \n");
								 // switch to build view
								 Window::factory->switchView('1');
								 // switch to build view sound in Window
								 
							 }
							 else{
								 //Explosion particle effect
								 //Explosion sound


							 }
							
							 break;
		}
		case TEventParticle:{
								printf("particle event received \n");
								//Window::factory->battlemode->PushGeoNode();
								break;
		}
		case TEventTimer:{
							 EventTimer * t = (EventTimer *)event;
							 printf("time event received \n");
							 //Change variable in build mode and battle mode

							 //CHANGE BATTLE MODE ONLY
							 int sec = t->time % 60;
							 Window::factory->battlemode->timer->secLeft = sec;
							 Window::factory->battlemode->timer->minLeft = (t->time - sec) / 60;
							 /////// end GUI

							 break;


		}
		case TEventScoreboard:{
								  EventScoreboard * s = (EventScoreboard *) event;
								  printf("scoreboard event received\n");

								  //Change score variables in battle mode and build mode
								  int myID = g_pCore->pPlayer->playerid;
								  int myScore = s->takedowns[myID] - s->deaths[myID];
								  
								  //calculate rank
								  int rank = 1;
								  for (int i = 0; i < 4; i++) {
									  if (i != myID) {
										  if (myScore < (s->takedowns[i] - s->deaths[i])) {
											  rank++;
										  }
									  }
								  }

								  Window::factory->score->updateScore(s->deaths[myID], s->takedowns[myID], rank);
								  /////// end GUI

								  break;

		}
		case TEventUpdateHealth:{
									//Update health bar
									EventHealth * h = (EventHealth *) event;
									printf("health event received\n");

									//this is for the GUI display update
									if (h->player1id == g_pCore->pPlayer->playerid) {
										Window::factory->battlemode->healthDisplay->currentHealth = h->health;
										Window::factory->battlemode->healthDisplay->maxHealth = h->maxhealth;
									}
									/////// end GUI

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