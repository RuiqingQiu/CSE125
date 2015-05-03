#pragma once
#include <string>


class GameEvents
{
protected:
	unsigned int _event_type;

public:
	GameEvents(int);
	~GameEvents();

	virtual void to_string(std::string&) = 0  ;
	int getType();

};

