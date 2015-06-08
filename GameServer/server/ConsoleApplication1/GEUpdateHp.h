#pragma once
#include "GameEvents.h"
class GEUpdateHp : public GameEvents
{


public:
	GEUpdateHp(int,int,int);
	~GEUpdateHp();
	//time in seconds
	int _cid;
	int _Hp;
	int _maxHp;

	void to_string(std::string&) override;
};

