#pragma once
#include "EventInfo.h"
class EventScoreboard :
	public EventInfo
{
public:
	int player1id;
	int player1_takedown;
	int player1_death;
	int player1_gold;

	int player2id;
	int player2_takedown;
	int player2_death;
	int player2_gold;

	int player3id;
	int player3_takedown;
	int player3_death;
	int player3_gold;

	int player4id;
	int player4_takedown;
	int player4_death;
	int player4_gold;
	EventScoreboard();
	~EventScoreboard();
};

