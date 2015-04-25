#pragma once



class GameEvents
{
private:
	unsigned int _event_type;

public:
	GameEvents(int);
	~GameEvents();

	virtual void to_string(char*) = 0  ;
	int getType();

};

