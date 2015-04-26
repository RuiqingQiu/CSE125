#pragma once
#include "Robot.h"
class DamageEvent
{

private:
	Robot* attacker;
	Robot* victim;
	GameObj* victimObj;
	int breakConstraint; //boolean, check to see if constraint should be broken

public:
	DamageEvent(Robot*, Robot*, GameObj*, int);
	~DamageEvent();

	Robot* getAttacker();
	Robot* getVictim();
	GameObj* getVictimObj();
	int getBreakConstraint();
};

