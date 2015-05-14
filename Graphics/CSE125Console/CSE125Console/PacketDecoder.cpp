#include "stdafx.h"
#include "PacketDecoder.h"
#include "Definition.h"
#include "EventDeath.h"
#include "EventDeath.h"
#include "EventParticle.h"
#include "EventTimer.h"
#include "EventScoreboard.h"
#include "EventHealth.h"
#include "EventCollision.h"
#include "EventWaiting.h"
#include "EventEmergency.h"


#define RAD_TO_DEGREE_MULT 57.2957795

PacketDecoder::PacketDecoder()
{
}


PacketDecoder::~PacketDecoder()
{
}

//Helper function for split strings
unsigned int split1(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos));

	return strs.size();
}


vector<EventInfo*> PacketDecoder::decodeEvent(string data)
{
	vector<EventInfo*> ret;
	std::vector<std::string> events;
	split1(data, events, '~');
	cout << data << endl;
	for (int i = 0; i < events.size()-1; i += 1){
		std::vector<std::string> EventData;
		split1(events[i], EventData, ' ');
		int EventId = stoi(EventData[0]);

		switch (EventId) {
			case TEventDeath:
			{
				printf("event death encode\n");
				EventDeath* EDeath = new EventDeath();
				EDeath->death_id = stoi(EventData[1]);
				EDeath->killer_id = stoi(EventData[2]);
				EDeath->processed = false;
				EDeath->event_type = TEventDeath;
				ret.push_back(EDeath);
				break;
			}
			case TEventParticle:
			{
				EventParticle* EParticle = new EventParticle();
				EParticle->particle_id = stoi(EventData[1]);
				EParticle->x = stof(EventData[2]);
				EParticle->y = stof(EventData[3]);
				EParticle->z = stof(EventData[4]);
				EParticle->processed = false;
				EParticle->event_type = TEventParticle;
				ret.push_back(EParticle);
				break;
			}
			case TEventTimer:
			{
				EventTimer* ETimer = new EventTimer();
				ETimer->time = stoi(EventData[1]);
				ETimer->processed = false;
				ret.push_back(ETimer);
				ETimer->event_type = TEventTimer;
				break;
			}
			case TEventScoreboard:
			{
				EventScoreboard* EScoreBoard = new EventScoreboard();
				for (int i = 0; i < 5; i++) {
				}

				EScoreBoard->playerid[0] = stoi(EventData[1]);
				EScoreBoard->takedowns[0] = stoi(EventData[2]);
				EScoreBoard->deaths[0] = stoi(EventData[3]);
				EScoreBoard->gold[0] = stoi(EventData[4]);


				EScoreBoard->playerid[1] = stoi(EventData[5]);
				EScoreBoard->takedowns[1] = stoi(EventData[6]);
				EScoreBoard->deaths[1] = stoi(EventData[7]);
				EScoreBoard->gold[1] = stoi(EventData[8]);

				EScoreBoard->playerid[2] = stoi(EventData[9]);
				EScoreBoard->takedowns[2] = stoi(EventData[10]);
				EScoreBoard->deaths[2] = stoi(EventData[11]);
				EScoreBoard->gold[2] = stoi(EventData[12]);

				EScoreBoard->playerid[3] = stoi(EventData[13]);
				EScoreBoard->takedowns[3] = stoi(EventData[14]);
				EScoreBoard->deaths[3] = stoi(EventData[15]);
				EScoreBoard->gold[3] = stoi(EventData[16]);

				EScoreBoard->processed = false;
				EScoreBoard->event_type = TEventScoreboard;
				ret.push_back(EScoreBoard);
				break;
			}
			case TEventUpdateHealth:
			{
				EventHealth* EHealth = new EventHealth();
				EHealth->player1id = stoi(EventData[1]);
				EHealth->health = stoi(EventData[2]);
				EHealth->maxhealth = stoi(EventData[3]);

				EHealth->processed = false;
				EHealth->event_type = TEventUpdateHealth;
				ret.push_back(EHealth);
				break;
			}
			case TEventCollisionHappen:
			{
				EventCollision* EEvent = new EventCollision();
				EEvent->collision_type = stoi(EventData[1]);
				EEvent->x = stof(EventData[2]);
				EEvent->y = stof(EventData[3]);
				EEvent->z = stof(EventData[4]);

				EEvent->processed = false;
				EEvent->event_type = TEventCollisionHappen;
				ret.push_back(EEvent);
				break;
			}
			case TEventWaiting:
			{
				EventWaiting* EWaiting = new EventWaiting();
				EWaiting->number_of_players = stoi(EventData[1]);
				EWaiting->processed = false;
				EWaiting->event_type = TEventWaiting;
				ret.push_back(EWaiting);
				break;
			}
			case TEventEmergency:
			{
				EventEmergency* EEmergency = new EventEmergency();
				EEmergency->processed = false;
				EEmergency->event_type = TEventEmergency;
				ret.push_back(EEmergency);
				break;
			}

			default:
			{
				//cout << "this is a good fix " << endl;
				break;
			}
		}
	}
	return ret;
}

vector<PlayerInfo*> PacketDecoder::decodePacket(string data)
{
	vector<PlayerInfo*> ret;
	std::vector<std::string> v;
	split1(data, v, ' ');
	/*
	for (int i = 0; i < v.size(); i++){
	cout << v[i] << endl;
	}*/
	if ((v.size()-1) % 8 != 0)
	{
		return ret;
	}
	//1 + 3 + 16
	for (int i = 0; i < v.size()-1; i += 8){
		PlayerInfo* p = new PlayerInfo();
		p->id = stoi(v[i]);
		p->x = stof(v[i + 1]);
		p->y = stof(v[i + 2]);
		p->z = stof(v[i + 3]);
		p->rx = stof(v[i + 4])*RAD_TO_DEGREE_MULT;
		p->ry = stof(v[i + 5])*RAD_TO_DEGREE_MULT;
		p->rz = stof(v[i + 6])*RAD_TO_DEGREE_MULT;
		p->type = stoi(v[i + 7]);
		//Check if this is something belong to that player
		p->processed = false;
		
		//p->print();
		/*
		for (int j = 0; j < 16; j++){
		p->mat[j] = stof(v[i + 4 + j]);
		// printf("%f, ", p->mat[j]);
		if (j % 4 == 0){
		//printf("\n");
		}
		}*/
		ret.push_back(p);
	}
	return ret;
}