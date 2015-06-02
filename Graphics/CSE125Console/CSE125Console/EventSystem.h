
#ifndef CSE125EventSystem
#define CSE125EventSystem
#include "GameInfoPacket.h"
#include "sound.h"

class EventSystem
{
public:
	EventSystem();
	~EventSystem();
	void ProcessGamePacket(GameInfoPacket* packet);
	Sound* sound; 
};

#endif

