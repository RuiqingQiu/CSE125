#include "DamageEvent.h"


DamageEvent::DamageEvent(Robot* a, Robot* v, GameObj* o, int b)
{
	attacker = a;
	victim = v;
	victimObj = o;
	breakConstraint = b;
}


DamageEvent::~DamageEvent()
{
}

Robot* DamageEvent::getAttacker()
{
	return attacker;
}
Robot* DamageEvent::getVictim()
{
	return victim;
}
GameObj* DamageEvent::getVictimObj()
{
	return victimObj;
}
int DamageEvent::getBreakConstraint()
{
	return breakConstraint;
}