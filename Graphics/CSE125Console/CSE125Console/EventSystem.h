#ifndef CSE125EventSystem
#define CSE125EventSystem
#include "GameInfoPacket.h"
class EventSystem
{
public:

	EventSystem();
	~EventSystem();
	void ProcessGamePacket(GameInfoPacket* packet);
};

#endif

